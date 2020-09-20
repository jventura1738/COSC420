#include "matrix.h"
int main(int argc, char** argv){
  MPI_Init(&argc, &argv); // pass through cli args
  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  // worldSize will be the total number of
  // nodes in the communicator.
  // myRank will be the nodes id within that
  // communicator
  int worldSize, myRank;

  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  srand(time(0));
  matrix A;
  
  initMatrix(&A, 8, 8);
  printMatrix(&A);

  matrix B;
  addMatrix(A, B, world, worldSize, myRank)
  MPI_Finalize();
  return 0;
}


