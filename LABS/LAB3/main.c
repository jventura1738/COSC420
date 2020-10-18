/*
 * Justin Ventura & Blaine Mason
 * COSC420 Lab 3: Gauss Jordan
 *
 * Dr. Joe Timothy Anderson
*/
#include<mpi.h>
#include "matrix.h"
int main(int argc, char ** argv) {
  srand(time(NULL));
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
  matrix A, b, aI, I, temp;
  matrix newb;
  initMatrix(&aI, 3, 3);
  initMatrix(&temp, 3, 3);
  initMatrix(&newb, 3, 1);
  initRandMatrix(&A, 3, 3);
  initRandMatrix(&b, 3, 1);
  initIMatrix(&I, 3, 3);
  printMatrix(&A);
  printMatrix(&b);
  newb.data = gauss_jordan(&A, &b, world, worldSize, 0);
  puts("");
  printf("The new b vector is:\n");
  printMatrix(&newb);
  puts("");
  aI.data = gauss_jordan(&A, &I, world, worldSize, 0);
  printf("The A inverse:\n");
  printMatrix(&aI);
  puts("");

  temp.data = multiplyMatrix(&A, &aI, world, worldSize, myRank);
  printf("A*AI:\n");
  printMatrix(&temp);
  puts("");
  

  return 0;
}
