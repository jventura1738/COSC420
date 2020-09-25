// Justin Ventura & Blaine Mason
// COSC420 Lab 2: main.c

#include "matrix.h"

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv); // pass through cli args

  int worldSize, myRank;

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
  
  // Arguments for matrix A
  int a1 = atoi(argv[1]);
  int a2 = atoi(argv[2]); 

  // Arguments for matrix B
  int b1 = atoi(argv[3]);
  int b2 = atoi(argv[4]); 

  // Make them jawns:
  matrix A, B, C;
  initRandMatrix(&A, a1,  a2);
  initRandMatrix(&B, b1,  b2);

  // Print A and B
  srand(time(NULL));
  if ( myRank == 0 ) {

    printMatrix(&A);
    puts("");
    printMatrix(&B);
    puts("");
    initMatrix(&C, a1,  b2);

  }
  
  // Add A and B:
  C.data = addMatrix(&A, &B, world, worldSize, myRank);
  if (myRank == 0) {

    printMatrix(&C);

  }

  // Multiply A and B:
  C.data = multiplyMatrix(&A, &B, world, worldSize, myRank);
  if ( myRank == 0) {

    printMatrix(&C);
  
  }

  MPI_Finalize();
  return 0;
  
}


