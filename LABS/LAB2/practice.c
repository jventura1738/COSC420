#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<math.h>
#include<string.h> // strcat

int main(int argc, char** argv){
  srand(time(0));
  MPI_Init(&argc, &argv);
  MPI_Comm world = MPI_COMM_WORLD;	  
  
  int worldSize, myRank;
  
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  int size = atoi(argv[1]);
  int i;
  int* a;
  int* b;
  if(myRank == 0){
    a = malloc(size*sizeof(int));
    b = malloc(size*sizeof(int));

    for(i = 0; i < size; i++){
      a[i] = rand() % 1000;
      b[i] = rand() % 1000;
    }

    int blockSize = ceil(size/worldSize);

  }

  int blockSize = size/worldSize;
  int* localA = malloc(blockSize*sizeof(int));
  int* localB = malloc(blockSize*sizeof(int));
  MPI_Scatter(a, blockSize, MPI_INT, localA, blockSize, MPI_INT, 0, world);
  MPI_Scatter(b, blockSize, MPI_INT, localB, blockSize, MPI_INT, 0, world);

  int Final = 0;
  for(i = 0; i < blockSize; i++){
    Final += localA[i] * localB[i];
  }

  int sum = 0;

  MPI_Reduce(&Final, &sum, 1, MPI_INT, MPI_SUM, 0, world);

  if (myRank == 0) {

    printf("Inner Product: %d\n", sum);//yo momma gay lol

  }
  MPI_Finalize();
  return 0;
}



