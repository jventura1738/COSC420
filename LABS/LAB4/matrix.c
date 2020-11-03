// Justin Ventura & Blaine Mason
// COSC420 Lab 3: matrix.c

#include "matrix.h"

#define MAX(a, b) (((a) > (b)) ? a : (b))
#define MIN(a, b) (((a) < (b)) ? a : (b))

//Creates a random rxc matrix 
void initRandMatrix(matrix *A, int rows, int cols) {
  
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
void copyMatrix(matrix *A, matrix *B) { 
  B->rows = A->rows;
  B->cols = A->cols;
  B->data = malloc(B->rows*B->cols*sizeof(double));
  int i,j;
  for(i=0; i < B->rows; i++) {

    for(j=0; j < B->cols; j++) {

      ACCESS(B,i,j) = ACCESS(A,i,j);

    }

  }
  
}
void initIMatrix(matrix *A, int rows, int cols) {
  
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));

  for(i=0; i < A->rows; i++) {

    for(j=0; j < A->cols; j++) {
      if(i == j){
        ACCESS(A,i,j) = 1;
      }else{
        ACCESS(A,i,j) = 0;
      }
      

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

      ACCESS(A,i,j) = 0.0;

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

  free(sendcts);
  free(displcmts);
  free(localA);
  free(localB);
  free(localSoln);

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

  free(sendcts);
  free(displcmts);
  free(localA);
  free(localB);
  free(localSoln);

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

  free(Bt.data);
  free(row_vect.data);
  free(col_vect.data);

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
  double Final = 0;
  for(i = 0; i < local_len; i++) {

    Final += localA[i] * localB[i];

  }
  
  // Now collect all the results from each node, and use
  // MPI_SUM to simplify the work.
  double sum = 0;
  MPI_Reduce(&Final, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, world);
  free(localA);
  free(localB);
  free(sendcts);
  free(displcmts);
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

/*
 * Gauss_Jordan.
 * 
 * This performs the gauss_jordan algorithm in parallel.
*/
double * gauss_jordan(matrix* A, matrix *b, MPI_Comm world, int worldSize, int myRank) {
  size_t i, k, r, c;
  matrix a;
  initMatrix(&a, A->rows, A->cols);
  matrix q;
  initMatrix(&q, b->rows, b->cols);
  matrix* cA = &a;
  matrix* cb = &q;
  copyMatrix(A, cA);
  copyMatrix(b, cb);

  //Below sendcts and displcmts are computed for matrix A
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));
  for(i=0; i<worldSize; i++){
    sendcts[i] = (cA->rows/worldSize)*cA->cols; // number each gets
  }
  for(i = 0; i < (cA->rows % worldSize); i++){
    sendcts[i] += cA->cols;
  }
  for(i=0; i<worldSize; i++){
    if(i == 0){
      displcmts[i] = 0; // start indicies
    }else{
      displcmts[i] = displcmts[i-1] + sendcts[i-1] ;
    }
  }

  //Below sendcts and displcmts are computed for matrix B(b)
  int *sendctsB = (int*) malloc(worldSize*sizeof(int));
  int *displcmtsB = (int*) malloc(worldSize*sizeof(int));
  for(i=0; i<worldSize; i++){
    sendctsB[i] = (cb->rows/worldSize)*cb->cols; // number each gets
  }
  for(i = 0; i < (cb->rows % worldSize); i++){
    sendctsB[i] += cb->cols;
  }
  for(i=0; i<worldSize; i++){
    if(i == 0){
      displcmtsB[i] = 0; // start indicies
    }else{
      displcmtsB[i] = displcmtsB[i-1] + sendctsB[i-1] ;
    }
  }
  for (k = 0; k < cA->rows; k++) {
    double* local_arrA = malloc(sendcts[myRank]*sizeof(double));
    double* local_arrB = malloc(sendctsB[myRank]*sizeof(double));
    double* kth_A = malloc(cA->rows*sizeof(double));
    double* kth_B = malloc(cb->rows*sizeof(double));
    double * scaling = malloc(cA->rows * sizeof(double));

    if(myRank == 0){
      for(i = 0; i < cA->rows; i++){
        scaling[i] = ACCESS(cA, i, k)/ACCESS(cA,k,k);
      }
      for(i = 0; i < cA->cols; i++){
        //kth row of A
        kth_A[i] = ACCESS(cA, k, i);
      }
      for(i = 0; i < cb->cols; i++){
        //kth row of B(b)
        kth_B[i] = ACCESS(cb, k, i);
      }
    }

    //MPI will BCAST on each iteration
    //1.) scaling
    //2.) kth_A
    //3.) kth_B
    MPI_Bcast(scaling, cA->rows, MPI_DOUBLE, 0, world);
    MPI_Bcast(kth_A, cA->rows, MPI_DOUBLE, 0, world);
    MPI_Bcast(kth_B, cb->rows, MPI_DOUBLE, 0, world);
    //MPI will Scatter on each iteration
    //1.) cA->data
    //2.) cb->data
    MPI_Scatterv(cA->data, sendcts, displcmts, MPI_DOUBLE, local_arrA, sendcts[myRank], MPI_DOUBLE, 0, world);
    MPI_Scatterv(cb->data, sendctsB, displcmtsB, MPI_DOUBLE, local_arrB, sendctsB[myRank], MPI_DOUBLE, 0, world);


    for(r = 0; r < sendcts[myRank]/cA->rows; r++){
      if(k == r+(displcmts[myRank]/cA->cols)){
        continue;
      }
      for(c = 0; c < cA->cols; c++){
        local_arrA[INDEX(cA,r,c)] = local_arrA[INDEX(cA,r,c)] - scaling[r + (displcmts[myRank]/cA->rows)]*kth_A[c];
      }
      for(c = 0; c < cb->cols; c++){
        local_arrB[INDEX(cb, r, c)] = local_arrB[INDEX(cb, r, c)] - scaling[r + (displcmtsB[myRank]/cb->cols)]*kth_B[c];
      }  
    }
    //MPI now gathers the data back
    MPI_Gatherv(local_arrA, sendcts[myRank], MPI_DOUBLE,
                cA->data, sendcts, displcmts,
                MPI_DOUBLE, 0, world);
    MPI_Gatherv(local_arrB, sendctsB[myRank], MPI_DOUBLE,
                cb->data, sendctsB, displcmtsB,
                MPI_DOUBLE, 0, world);
    free(scaling);
    free(local_arrA);
    free(local_arrB);
    free(kth_A);
    free(kth_B);
  }
  //The master node does the multiplying 
  //after the matrix is put into row reduced form
  if(myRank == 0){
    double* scalingL = malloc((cA->cols)*sizeof(double));
    for(i = 0; i < cA->rows; i++){
      for(k = 0; k < cA->cols; k++){
        if(i == k){
          scalingL[i] = ACCESS(cA,i,k);
        } 
      }
    }

    for(i = 0; i < cA->rows; i++){
      for(k = 0; k < cA->cols; k++){
        ACCESS(cA, i, k) = ACCESS(cA, i, k)/scalingL[i];
      }
    }
    if(cb->cols > 1){
      for(i = 0; i < cb->rows; i++){
        for(k = 0; k < cb->cols; k++){
          ACCESS(cb, i, k) = ACCESS(cb, i, k) / scalingL[i];
        }
      }
    }else{
      for(i = 0; i < cb->rows; i++){
        ACCESS(cb, i, 0) = ACCESS(cb, i, 0) / scalingL[i];
      }
    }
    free(sendcts);
    free(displcmts);
    free(sendctsB);
    free(displcmtsB);
  }

  return cb->data;
}


double * normalize(matrix *v, MPI_Comm world, int worldSize, int myRank) {

  if(!v->data) {

    printf("No vector to normalize buddy.\n");
    return NULL;

  }

  /* Step 1: get the Euclidean Norm. */
  
  int terms = MAX(v->cols, v->rows);
  int nodes = MIN(terms, worldSize);

  int y;

  if (myRank == 0) {

    puts("x:");
    for (y = 0; y < terms; y++) {

      printf("%f ", v->data[y]);

    }

    puts("");

  }

  double * normalized_v = (double*) malloc(sizeof(double) * terms);

  int * sndcts = (int*) malloc(worldSize*sizeof(int));
  int * displs = (int*) malloc(worldSize*sizeof(int));

  int n;
  for (n = 0; n < worldSize; n++) {

    if (n > nodes) {

      sndcts[n] = 1;
      displs[n] = n-1;

    }
    else {

      sndcts[n] = 0;
      displs[n] = 0;

    }

  }

  n = 0;
  while (n < terms) {

    sndcts[n % nodes] += 1;
    n += 1;

  }
  displs[0] = 0;
  int displacement = 0;
  for (n = 1; n < nodes; n++) {

    displacement += sndcts[n-1];
    displs[n] += displacement;

  }

  MPI_Bcast(v->data, terms, MPI_DOUBLE, 0, world);

  double local_sum = 0;
  if (myRank < nodes) {

    for (n = displs[myRank]; n < displs[myRank] + sndcts[myRank]; n++) {

      local_sum += v->data[n] * v->data[n];

    }

  }

  double final = 0.0;
  MPI_Reduce(&local_sum, &final, 1, MPI_DOUBLE, MPI_SUM, 0, world);

  if (myRank == 0) {

    final = sqrtf(final);
    printf("\nSqrt of the sum of squares: %f\n", final);
    puts("Normalizing.\n");

  }

  /* Step 2: Normalize v by dividing each entry of v by the L2Norm(v). */

  MPI_Bcast(&final, 1, MPI_DOUBLE, 0, world);
  //printf("displs[%d] = %d\n", myRank, displs[myRank]);
  //DISPLS[0] = 0, so local_v is empty
  //So we cannot write to it

  double * local_v = (double*) malloc(sizeof(double) * sndcts[myRank]);
  //printf("I created local_v\n");
  MPI_Scatterv(normalized_v, sndcts, displs, MPI_DOUBLE, local_v, sndcts[myRank], MPI_DOUBLE, 0, world);

  if (myRank < nodes) {

    for (n = 0; n < sndcts[myRank]; n++) {

      //printf("local_v[%d] = %f\n", n, v->data[displs[myRank] + n] / final);
      local_v[n] = v->data[displs[myRank] + n] / final;
    
    }

  }

  MPI_Barrier(world);

  MPI_Gatherv(local_v, sndcts[myRank], MPI_DOUBLE, normalized_v, sndcts, displs, MPI_DOUBLE, 0, world);

  free(sndcts);
  free(displs);

  return normalized_v;

}
