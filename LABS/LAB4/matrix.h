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

/* Matrix initializers, copiers, printers. */
void initRandMatrix(matrix *A, int rows, int cols);
void copyMatrix(matrix *A, matrix *B);
void initMatrix(matrix *A, int rows, int cols);
void initIMatrix(matrix *A, int rows, int cols);
void printMatrix(matrix *A);

/* 
 * Matrix operations:
 *
 * - Matrix Transposition.
 *   -> takes a matrix A, and returns the
 *      transpose: [for a matrix A, return 
 *      matrix B s.t. Bij = Aji]
 *
 * - Matrix Addition & Subtraction.
 *   -> Given equal dimension matrices A &
 *      B, return matrix C s.t. Cij = Aij
 *      +- Bij.
 *
 * - Matrix Multiplication.
 *   -> Given proper matrices A, B, return
 *      matrix C s.t. Cij = Arowi dot BTrowj.
 *
 * - Inner Product.
 *   -> Given two vectors, returns a double d
 *      s.t. d = sum(Ai * Bi for all i).
 *
 * - Gauss-Jordan Elimination.
 *   -> For system Ax = b, calculate the soln
 *      x that satisfies the system.  The soln
 *      will be a modified copy of b.  This can
 *      also be used to perform matrix inversion
 *      where a modified b will be the inverse.
*/

matrix transpose(matrix *A);
double * addMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);  
double * subtractMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double * multiplyMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double innerProduct(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank);
double * gauss_jordan(matrix *A, matrix *b, MPI_Comm world, int worldSize, int myRank);

#endif
