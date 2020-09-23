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

  int b1 = atoi(argv[3]);
  int b2 = atoi(argv[4]); 

  matrix A, B, C;
  initRandMatrix(&A, a1,  a2);
  initRandMatrix(&B, b1,  b2);

  srand(time(NULL));
  if ( myRank == 0 ) {
    //printMatrix(&A);
    //puts("");
    //printMatrix(&B);
    //puts("");
    initMatrix(&C, a1,  b2);
  }
  
  //C.data = addMatrix(&A, &B, world, worldSize, myRank);
  C.data = multiplyMatrix(&A, &B, world, worldSize, myRank);
  //printMatrix(&A);
  //puts("");
  //C.data = transpose(&A);
  if ( myRank == 0) {

    //printMatrix(&C);
  

  }

  MPI_Finalize();
  return 0;
}


