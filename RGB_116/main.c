// Justin Ventura & Blaine Mason
// Project Euler Problem 116

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(int argc, char** argv) {

  MPI_Init(&argc, &argv); // pass through cli args

  // # nodes and each nodes rank.
  int worldSize, myRank;

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  /*
   * Hardcode example.  Let N be 5, that is,
   * 5 blocks.  Red blocks will take up 2,
   * green 3, blue 4.
   *
   * Thus, we should have 7 + 3 + 2 = 12.
   *
  */


  /* ALG START */

  // Distribute the work to all nodes

  // Have equiv 0 mod 3 work on red   (2)
  //            1 mod 3 work on green (3)
  //            2 mod 3 work on blue  (4)



  /* ALG END */

  MPI_Finalize();
  return 0;

}