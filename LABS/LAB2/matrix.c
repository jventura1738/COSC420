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
  
  /*
	for (size_t i = 0; i < A.row; i++) {

		for (size_t j = 0; j < B.col; j++) {

			C.M[i * C.col + j] = 0; 

			for (size_t k = 0; k < A.col; k++) {

				C.M[i * C.col + j] += A.M[i * A.col + k] * B.M[k * B.col + j];

			}

		}

	}
  */

	return C;

}
