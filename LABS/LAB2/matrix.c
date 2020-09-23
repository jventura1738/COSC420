
#include"matrix.h"

void initRandMatrix(matrix *A, int rows, int cols){
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      ACCESS(A,i,j) = rand() % 10 + 1;
    }
  }
}

void initMatrix(matrix *A, int rows, int cols){
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      ACCESS(A,i,j) = 0;
    }
  }
}

void printMatrix(matrix *A){
  int i,j;
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      printf("%0.2f ", ACCESS(A,i,j));
    }
    puts("");
  }
}

double * addMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  
  if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;
    
  }
  
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  double* C = malloc(len*sizeof(double));
  //printf("Len: %d BlockSize: %d", len, blockSize);
  //puts("");
  
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));
  

  MPI_Scatter(A->data, blockSize, MPI_DOUBLE, localA, blockSize, MPI_DOUBLE, 0, world);
  MPI_Scatter(B->data, blockSize, MPI_DOUBLE, localB, blockSize, MPI_DOUBLE, 0, world);
  
  int i;
  //printf("I am node %d", myRank);
  //puts("");
  for(i = 0; i < blockSize; i++) {
    localSoln[i] = localA[i] + localB[i];
    //printf("%f ", localSoln[i]);
  }
  //puts("");
  
  MPI_Gather(localSoln, blockSize, MPI_DOUBLE, C, blockSize, MPI_DOUBLE, 0, world);

  return C;

}

double * subtractMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;
    
  }
  
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  double* C = malloc(len*sizeof(double));
  //printf("Len: %d BlockSize: %d", len, blockSize);
  //puts("");
  
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));
  

  MPI_Scatter(A->data, blockSize, MPI_DOUBLE, localA, blockSize, MPI_DOUBLE, 0, world);
  MPI_Scatter(B->data, blockSize, MPI_DOUBLE, localB, blockSize, MPI_DOUBLE, 0, world);
  
  int i;
  //printf("I am node %d", myRank);
  //puts("");
  for(i = 0; i < blockSize; i++) {
    localSoln[i] = localA[i] - localB[i];
    //printf("%f ", localSoln[i]);
  }
  //puts("");
  
  MPI_Gather(localSoln, blockSize, MPI_DOUBLE, C, blockSize, MPI_DOUBLE, 0, world);

  return C;
}

double * multiplyMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  if (A->cols != B->rows) {
		printf("matrices must have A.col == B.row");
    return 0;
	}
  if (worldSize > A->cols * B->rows) {
    printf("yo momma SOOO fat....\n");
    return 0;
  }
  int finalRows = A->rows;
  int finalCols = B->cols;
  matrix A2;
  matrix B2;
  initMatrix(&A2, 1,  A->cols);
  initMatrix(&B2, B->rows,  1);
  
  srand(time(NULL) + myRank);
  int i, j, k;
  int len = finalRows*finalCols;
  double* final = malloc(len*sizeof(double));
  if (myRank == 0){
    for(i = 0; i < len; i++){
      final[i] = 0;
    } 
  }
  
  for(j=0; j < finalRows; j++){
    for(k=0; k < finalCols; k++){
      if(myRank == 0){
        for(i= 0; i< A->cols; i++){
          A2.data[i] = ACCESS(A,j,i);
        }for(i= 0; i< B->rows; i++){
          B2.data[i] = ACCESS(B,i,k);
        }
      }
      final[INDEX(B,j,k)] = innerProduct(&A2, &B2, world, worldSize, myRank);
    }
  }
  
  return final;

	

}
double innerProduct(matrix* A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  int size = A->cols;
  int i;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  for(i=0; i<worldSize; i++){
    sendcts[i] = size/worldSize; // number each gets
    displcmts[i] = i*(size/worldSize); // start indicies
  }

  if( size % worldSize > 0 ){
    //printf("N is not divisible by %d\n", worldSize);
    int extra = size % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy
  }
  if(myRank == 0){
    int blockSize = ceil(size/worldSize);

  }
   
  double local_len = sendcts[myRank];
  double* localA = malloc(local_len*sizeof(double));
  double* localB = malloc(local_len*sizeof(double));
  
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localA, local_len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localB, local_len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info

  int Final = 0;
  for(i = 0; i < local_len; i++){
    Final += localA[i] * localB[i];
  }

  int sum = 0;
  MPI_Reduce(&Final, &sum, 1, MPI_INT, MPI_SUM, 0, world);

  if (myRank == 0) {

    //printf("Inner Product: %d\n", sum);//yo momma gay lol

  }
  return sum;
}


double* transpose(matrix* A){
  int i,j;
  double* temp = malloc(A->rows*A->cols*sizeof(double)); 

  for(i = 0; i < A->cols; i++){
    for(j = 0; j < A->rows; j++){
      temp[i*A->rows + j] = ACCESS(A, j, i);  
    }
  }
    
  return temp;
}

