// Justin Ventura & Blaine Mason
// COSC420 Lab 3: matrix.c

#include"matrix.h"

//Creates a random rxc matrix 
void initRandMatrix(matrix *A, int rows, int cols) {
  srand(time(NULL));
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));

  for(i=0; i < A->rows; i++) {

    for(j=0; j < A->cols; j++) {

      ACCESS(A,i,j) = rand() % 10 + 1;

    }

  }

}

//Creates a rxc matrix with 0 as the value
void initMatrix(matrix *A, int rows, int cols) {
  
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));

  for(i=0; i < A->rows; i++) {

    for(j=0; j < A->cols; j++) {

      ACCESS(A,i,j) = 0;

    }

  }

}

//Prints out the matrix
void printMatrix(matrix *A) {

  int i,j;
  for(i=0; i < A->rows; i++) {

    for(j=0; j < A->cols; j++) {

      printf("%0.2f ", ACCESS(A,i,j));


    }
    puts("");

  }

}

/*
 * Matrix Addition Method.
 * 
 * This takes two matrices, and performs matrix
 * addition in parallel.
*/
double * addMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){

  // This is the requirement.
  if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;

  }

  // Variables
  int i;
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  // This is for uneven division between blocks and nodes.
  for(i=0; i<worldSize; i++) {

    sendcts[i] = len/worldSize;       // number each gets
    displcmts[i] = i*(len/worldSize); // start indicies

  }

  // This cleans the extras using small brain.
  if( len % worldSize > 0 ) {

    int extra = len % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy

  }

  // Arrays for work.
  double* C = malloc(len*sizeof(double));
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));

  // Scatter the arrays...
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localA, len, MPI_DOUBLE,                 // recv info
      0, world);                               // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localB, len, MPI_DOUBLE,                 // recv info
      0, world);                               // misc info

  // Perform the addition locally (on the node).
  for(i = 0; i < blockSize; i++) {

    localSoln[i] = localA[i] + localB[i];

  }

  // Gather the results, and store them into C to return.
  MPI_Gatherv(localSoln, blockSize, MPI_DOUBLE, C, sendcts, displcmts, MPI_DOUBLE, 0, world);

  return C;

}

/*
 * Matrix Subtraction Method.
 * 
 * This takes two matrices, and performs matrix
 * subtraction in parallel.
*/
double * subtractMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank) {

    // This is the requirement
  if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;

  }

  // Variables
  int i;
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  // These two sections are for uneven divisions.
  for(i=0; i<worldSize; i++) {

    sendcts[i] = len/worldSize;       // number each gets
    displcmts[i] = i*(len/worldSize); // start indicies

  }
  if( len % worldSize > 0 ){
    int extra = len % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy
  }

  // Local arrays.
  double* C = malloc(len*sizeof(double));
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));

  // Scatter the blocks across the nodes.
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localA, len, MPI_DOUBLE,                 // recv info
      0, world);                               // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localB, len, MPI_DOUBLE,                 // recv info
      0, world);                               // misc info

  // Peform the subtraction locally (on the node).
  for(i = 0; i < blockSize; i++) {

    localSoln[i] = localA[i] - localB[i];

  }

  // Gather the results, combine then return as C.
  MPI_Gatherv(localSoln, blockSize, MPI_DOUBLE, C, sendcts, displcmts, MPI_DOUBLE, 0, world);

  return C;

}

/*
 * Matrix Multiplication Method.
 * 
 * This takes two matrices, and performs matrix
 * multiplication in parallel (the inner products
 * themselves are in parallel).
 * 
 * Algorithm:
 * 
 * - Assert the correct matrices.
 * - Create bt as Transpose of B.
 * - Then grab each row of A.
 * - Inner_Prod that row by each in B. 
 * - Repeat until all rows in A done.
 * - Store each result into the final.
 * - Return final.
*/
double * multiplyMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank) {

  // This is the requirement.
  if (A->cols != B->rows) {

		printf("matrices must have A.col == B.row");
    return 0;

	}

  // Don't use more nodes than we have possible
  // entries in the matrix :)
  if (worldSize > A->cols * B->rows) {

    printf("Just jokes....\n");
    return 0;

  }

  // These are the variables and object we need.
  matrix Bt;
  Bt = transpose(B);
  int i, j, k;
  matrix row_vect, col_vect;
  row_vect.rows = 1;
  row_vect.cols = A->cols;
  row_vect.rows = 1;
  row_vect.cols = A->cols;
  row_vect.data = malloc(A->cols * sizeof(double));
  col_vect.data = malloc(A->cols * sizeof(double));

  // Make all vectors full of zeroes.
  for (i = 0; i < A->cols; i++) {

    row_vect.data[i] = 0;
    col_vect.data[i] = 0;

  }

  srand(time(NULL));

  // We will return this 'final'.
  int len = A->rows*Bt.rows;
  double* final = malloc(len*sizeof(double));
  if (myRank == 0){
    for(i = 0; i < len; i++){

      final[i] = 0;

    } 
    
  }

  /*  - ALG START -  */

  // Iterate the rows of A.
  for(i=0; i < A->rows; i++) {

    // Each row of A gets all rows in Bt.
    for(j=0; j < Bt.rows; j++) {

      // Here we extract the row and col vectors from
      // A (row vect of A) and Bt (col vect of B).
      for(k= 0; k< A->cols; k++) {

        row_vect.data[k] = ACCESS(A,i,k);
        col_vect.data[k] = Bt.data[j * A->cols + k];

      }

      // Take those vectors, and add the inner_prod of them to the final matrix.
      final[INDEX(B,i,j)] = innerProduct(&row_vect, &col_vect, world, worldSize, myRank);

    }

  }

  // Finally :)
  return final;

}

/*
 * Vector Inner-Product Method.
 * 
 * This takes two matrices (as vectors), and performs the
 * inner product in parallel.
*/
double innerProduct(matrix* A, matrix *B, MPI_Comm world, int worldSize, int myRank) {

  // Variables
  int size = A->cols;
  int i;
  int * sendcts = (int*) malloc(worldSize*sizeof(int));
  int * displcmts = (int*) malloc(worldSize*sizeof(int));

  // This is for uneven divisions between the blocks
  // and nodes.
  for(i=0; i<worldSize; i++) {

    sendcts[i] = size/worldSize; // number each gets
    displcmts[i] = i*(size/worldSize); // start indicies
  
  }

  if(size % worldSize > 0) {

    int extra = size % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy

  }

  // This is for the block sizes.
  if(myRank == 0){
    int blockSize = ceil(size/worldSize);

  }

  // Local arrays for the inner product.
  double local_len = sendcts[myRank];
  double* localA = malloc(local_len*sizeof(double));
  double* localB = malloc(local_len*sizeof(double));

  // Scatter the blocks to each nodes.
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localA, local_len, MPI_DOUBLE,           // recv info
      0, world);                               // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE, // send info
      localB, local_len, MPI_DOUBLE,           // recv info
      0, world);                               // misc info

  // Perform the inner product.
  int Final = 0;
  for(i = 0; i < local_len; i++) {

    Final += localA[i] * localB[i];

  }
  
  // Now collect all the results from each node, and use
  // MPI_SUM to simplify the work.
  int sum = 0;
  MPI_Reduce(&Final, &sum, 1, MPI_INT, MPI_SUM, 0, world);
  free(localA);
  free(localB);
  // Return the inner product :)
  return sum;
}

/*
 * Matrix Transpose Method.
 * 
 * This performs the transpose of a matrix
 * in serial.
*/
matrix transpose(matrix* A) {

  matrix At;
  At.rows = A->cols;
  At.cols = A->rows;
  At.data = malloc(A->rows * A->cols * sizeof(double));
  int i,j;

  // Finessed from my 320 matrix class :)
  for(i = 0; i < A->cols; i++) {

    for(j = 0; j < A->rows; j++) {

      At.data[i*A->rows + j] = ACCESS(A, j, i);  

    }

  }

  return At;
}


void gauss_jordan(matrix* A, matrix *b, MPI_Comm world, int worldSize, int myRank) {


  size_t i, k, r, c;

  for (k = 0; k < A->rows; k++) {
    
    double * scaling = malloc(A->rows * sizeof(double));
    for(i = 0; i < A->rows; i++){
      scaling[i] = ACCESS(A, i, k)/ACCESS(A,k,k);
    }
    for(r = 0; r < A->rows; r++){
      if(r == k){
        continue;
      }
      for(c = 0; c < A->cols; c++){
        ACCESS(A, r, c) = ACCESS(A, r, c) - scaling[r]*ACCESS(A,k,c);
      }
      for(c = 0; c < b->cols; c++){
        ACCESS(b, r, c) = ACCESS(b, r, c) - scaling[k]*ACCESS(b,k,c);
      }  
    }
  }

  printMatrix(A);

}