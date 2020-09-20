#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
// NB: the A here needs to be a struct, not a pointer!
#define INDEX(A,i,j) A->cols*i + j
// now can do A.data[INDEX(A,i,j)]

// use the above to shortcut accessing the array
#define ACCESS(A,i,j) A->data[INDEX(A,i,j)]

// C needs the "typedef"
typedef struct {
  int rows, cols; // dimensions
  double* data;   // pointer to the data, a flat array
} matrix;

void initMatrix(matrix *A, int rows, int cols);
void printMatrix(matrix *A);
void addMatrix(matrix *A, matrix *B, int world, int worldSize, int myRank);   
#endif
