#include "matrix.h"
#include "mpi.h"

int main(int argc, char** argv) {

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

  printf("test\n");

  MPI_Finalize();
  return 0;
}