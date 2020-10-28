#include "matrix.h"

int main(int argc, char** argv) {

  srand(0);
  MPI_Init(&argc, &argv);

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  // worldSize will be the total number of
  // nodes in the communicator.
  // myRank will be the nodes id within that
  // communicator.
  int worldSize, myRank;

  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  /* do work */

  matrix A;
  matrix e;
  int z;
  e.data = malloc(sizeof(double) * 3);
  e.rows = 3;
  e.cols = 1;
  for (z = 0; z < 3; z++) e.data[z] = 1;

  initRandMatrix(&A, 3, 3);
  
  matrix x;
  x.data = multiplyMatrix(&A, &e, world, worldSize, myRank);
  x.rows = e.rows;
  x.cols = e.cols;
  if (myRank == 0) {

    puts("x:");
    printMatrix(&x);

  }
  

  normalize(&x, world, worldSize, myRank);

  /* end work */

  MPI_Barrier(world);

  free(A.data);
  free(e.data);
  free(x.data);
  MPI_Finalize();

  return 0;
}