#include "matrix.h"
#define DIM 4

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
  e.data = malloc(sizeof(double) * DIM);
  e.rows = DIM;
  e.cols = 1;
  for (z = 0; z < DIM; z++) e.data[z] = 1;

  initRandMatrix(&A, DIM, DIM);
  
  matrix x;
  x.data = multiplyMatrix(&A, &e, world, worldSize, myRank);
  x.rows = e.rows;
  x.cols = e.cols;
  if (myRank == 0) {

    puts("x:");
    printMatrix(&x);

  }
  

  double * test = normalize(&x, world, worldSize, myRank);

  if (myRank == 0) {

    int i;
    for (i = 0; i < DIM; i++) {

      printf("%f ", test[i]);

    }

    puts("");

  }

  /* end work */

  MPI_Barrier(world);

  free(A.data);
  free(e.data);
  free(x.data);
  MPI_Finalize();

  return 0;
}