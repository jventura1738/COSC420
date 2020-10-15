/*
 * Justin Ventura & Blaine Mason
 * COSC420 Lab 3: Gauss Jordan
 *
 * Dr. Joe Timothy Anderson
*/
#include<mpi.h>
#include "matrix.h"
int main(int argc, char ** argv) {
  
  // MPI Business.
  MPI_Init(&argc, &argv);

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  int worldSize, myRank;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  // TODO: read from file to get matrix & vect.

  /*
  * Gauss-Jordan Elimination Algorithm.
  *
  * Performs the standard Gauss-Jordan
  * elimination algorithm for row reduction
  * in order to solve the linear system of
  *
  * -> Ax = b
  *
  * In  -> n*m Matrix A
  *        n*1 vector b
  *        MPI information.
  *
  * Out -> The solution vector "x".
  */

  // TODO: Perform alg.
  matrix A, b;
  initRandMatrix(&A, 5, 5);
  initRandMatrix(&b, 5, 1);
  printMatrix(&A);
  printMatrix(&b);
  gauss_jordan(&A, &b, world, worldSize, 0);

  return 0;
}
