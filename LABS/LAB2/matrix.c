
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

  srand(time(NULL) + myRank);
  int i, j, k;
  int nodes = A->rows*B->cols;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  for(i=0; i<worldSize; i++){
    sendcts[i] = nodes/worldSize; // number each gets
    displcmts[i] = i*(nodes/worldSize); // start indicies
  }
  if( nodes % worldSize > 0 ){
    //printf("N is not divisible by %d\n", worldSize);
    int extra = nodes % worldSize;
    sendcts[worldSize-1] += extra;
  }
  

  int len = A->rows*B->cols;
  double* final = malloc(len*sizeof(double));
  if (myRank == 0){
    for(i = 0; i < len; i++){
      final[i] = 0;
    }
    puts("");

    MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE,// send info
      final, len, MPI_DOUBLE,   // recv info
      0, world);  
    MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE,// send info
      final, len, MPI_DOUBLE,   // recv info
      0, world);  
  }

  for(j=0; j < B->cols; j++){
    for(k=0; k < A->cols; k++){
      final[myRank*B->cols + j] += ACCESS(A,myRank,k)*ACCESS(B,k,j);
    }
  }
  return final;

	

}
