#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<math.h>

int main(int argc, char** argv){
  srand(time(0));
  MPI_Init(&argc, &argv);
  MPI_Comm world = MPI_COMM_WORLD;

  int worldSize, myRank;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
  
  int size, i;
  int* a;
  int* b;

  if(myRank == 0){
    size = atoi(argv[1]);
    a = malloc(size*sizeof(int));
    b = malloc(size*sizeof(int));

    for(i = 0; i < size; i++){
      a[i] = rand() % 10000;
      b[i] = rand() % 10000;
    }

  }
 
  int blockSize = ceil(size/worldSize);
  
  printf("Vector 1: \n");
  for(i = 0; i< size; i++){
    printf("%d ", a[i]); 
  }
  printf("\nVector 2: \n"); 
  for(i = 0; i< size; i++){
    printf("%d ", b[i]); 
  }
  
  



  MPI_Finalize();
  return 0;
}



