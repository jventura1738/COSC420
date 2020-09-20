#include"matrix.h"

void initMatrix(matrix *A, int rows, int cols){
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

void printMatrix(matrix *A){
  int i,j;
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      printf("%0.2f ", ACCESS(A,i,j));
    }
    puts("");
  }
}

