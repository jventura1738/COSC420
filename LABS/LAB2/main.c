#include "matrix.h"
int main(int argc, char** argv){
  MPI_Init(&argc, &argv); // pass through cli args

  int worldSize, myRank;
  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
  
  int a1 = atoi(argv[1]);
  int a2 = atoi(argv[2]);  

  matrix A, B, C;
  initRandMatrix(&A, a1,  a2);
  initRandMatrix(&B, a1,  a2);
  initMatrix(&C, a1,  a2);

  srand(time(NULL));
  if ( myRank == 0 ) {
    //printMatrix(&A);
    //puts("");
    //printMatrix(&B);
    //puts("");
    initMatrix(&C, a1,  a2);
  }
  
  C.data = addMatrix(&A, &B, world, worldSize, myRank);
  if ( myRank == 0) {

    //printMatrix(&C);
  
  }

  MPI_Finalize();
  return 0;
}


