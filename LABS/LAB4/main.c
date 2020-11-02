#include "matrix.h"
#define DIM 3
#define LIMIT 10
#define VERBOSE 1

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
  int z, count = 0, success = 0;
  e.data = malloc(sizeof(double) * DIM);
  e.rows = DIM;
  e.cols = 1;
  matrix x;
  x.data = malloc(sizeof(double) * DIM);
  x.rows = e.rows;
  x.cols = e.cols;
  for (z = 0; z < DIM; z++) {
    
    e.data[z] = 1;
    x.data[z] = 1;

  }
  initRandMatrix(&A, DIM, DIM);

  if (myRank == 0) {

    puts("A:");
    printMatrix(&A);

  }
  
  while (count < LIMIT && !success) {

    x.data = multiplyMatrix(&A, &x, world, worldSize, myRank);
    double * new_x = normalize(&x, world, worldSize, myRank);
    free(x.data);
    x.data = new_x;

    if (myRank == 0 && VERBOSE) {

      printf("x after pass %d:\n", count);
      int i;
      for (i = 0; i < DIM; i++) {

        printf("%f ", x.data[i]);

      }

      puts("");

    }

    double * test = subtractMatrix(&e, &x, world, worldSize, myRank);
    
    MPI_Bcast(test, DIM, MPI_DOUBLE, 0, world);

    int i, sum = 0;
    for (i = 0; i < DIM; i++) {

      sum += test[i];

    }

    if (DIM - sum <= 0.0001) {

      success = 1;

    }

    free(test);

    count++;

    MPI_Barrier(world);
    
  }

  if (myRank == 0) {

    if (success) {

      puts("x:");
      printMatrix(&x);

    }
    else {

      puts("you suck, x:");
      printMatrix(&x);

    }

  }

  /* end work */

  MPI_Barrier(world);

  free(A.data);
  free(e.data);
  free(x.data);

  MPI_Finalize();

  return 0;
}