/*
 * Justin Ventura & Blaine Mason
 * COSC420 Lab 3: Gauss Jordan
 *
 * Dr. Joe Timothy Anderson
*/
#include<mpi.h>
#include "matrix.h"
int main(int argc, char ** argv) {
  //srand(time(NULL));
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
  int n = 2000;
  matrix A, b, aI, I, temp;
  matrix newb;
  initMatrix(&aI, n, n);
  initMatrix(&temp, n, n);
  initMatrix(&newb, n, 1);
  initRandMatrix(&A, n, n);
  initRandMatrix(&b, n, 1);
  initIMatrix(&I, n, n);
  if(myRank == 0){
    //printMatrix(&A);
    //printMatrix(&b);
  }
  newb.data = gauss_jordan(&A, &b, world, worldSize, myRank);
  if(myRank == 0){
    puts("");
    printf("The new b vector is:\n");
    printMatrix(&newb);
    puts("");
  }
  /*
  aI.data = gauss_jordan(&A, &I, world, worldSize, myRank);
  if(myRank == 0){
    printf("The A inverse:\n");
    printMatrix(&aI);
    puts("");
  }
  temp.data = multiplyMatrix(&A, &aI, world, worldSize, myRank);
  if(myRank == 0){
    printf("A*AI:\n");
    printMatrix(&temp);
    puts("");
  }
  */
  MPI_Finalize();
  return 0;
}
