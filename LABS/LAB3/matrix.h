// Justin Ventura & Blaine Mason
// COSC420 Lab 3: matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
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

/*
 * Matrix fillers and operations.
*/
void initRandMatrix(matrix *A, int rows, int cols);
void copyMatrix(matrix *A, matrix *B);
void initMatrix(matrix *A, int rows, int cols);
void initIMatrix(matrix *A, int rows, int cols);
void printMatrix(matrix *A);
matrix transpose(matrix* A);
double * addMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);  
double * subtractMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double * multiplyMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double innerProduct(matrix* A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double * gauss_jordan(matrix* A, matrix *b, MPI_Comm world, int worldSize, int myRank);
#endif
