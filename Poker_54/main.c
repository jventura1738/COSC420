// Justin Ventura & Blaine Mason
// Project Euler Problem 54

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "mpi.h"

size_t choose(size_t n, size_t k) {

  size_t i, quotient = 1;
  for (i = 1; i <= k; i++) {

    quotient *= n;
    quotient /= i;
    n--;

  }

  return quotient;

}


int main(int argc, char** argv) {

  MPI_Init(&argc, &argv); // pass through cli args

  // # nodes and each nodes rank.
  int worldSize, myRank;

  // // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  int tile_count = atoi(argv[1]);

  /* ALG START */

  // Distribute the work to all nodes

  // Have equiv 0 mod 3 work on red   (2)
  //            1 mod 3 work on green (3)
  //            2 mod 3 work on blue  (4)
  size_t local_sum = 0;

  if (myRank % 3 == 0) {

    size_t i, max_red = tile_count / 2;
    for (i = 1; i <= max_red; i++) {

      local_sum += choose(tile_count - i, i);

    }

  }
  else if (myRank % 3 == 1) {

    size_t i, max_grn = tile_count / 3;
    for (i = 1; i <= max_grn; i++) {

      local_sum += choose(tile_count - i * 2, i);

    }

  }
  else {

    size_t i, max_blu = tile_count / 4;
    for (i = 1; i <= max_blu; i++) {

      local_sum += choose(tile_count - i * 3, i);

    }

  }

  size_t final = 0;

  MPI_Reduce(&local_sum, &final, 1, MPI_INT, MPI_SUM, 0, world);
  
  if (myRank == 0)
    printf("result = %zu\n", final);

  /* ALG END */
  MPI_Finalize();

  return 0;

}