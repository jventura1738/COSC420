#include <stddef.h>
#include <stdio.h>
#include "mpi.h"

size_t C(size_t n, size_t k) {
  size_t res = 1;
  size_t i;
  for(i = 1; i <=k; ++i){
    res = res * (n - k + i) / i;
  }
  return (size_t)(res + 0.01);
}

int main(int argc, char** argv){
  MPI_Init(&argc, &argv); // pass through cli args
  int worldSize, myRank;

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank); 
  size_t i, j;
  size_t n = 100000;
  size_t count = 0;
  int range, low, high;
  range = n/worldSize;
  if(myRank == 0){
    low = 0;
    high = low + range;
  }else{
    low = myRank*range;
    high = low + range;
  }
  for(i = low; i < high; i++){
    for(j = 0; j <= i; j++){
      if (C(i, j) % 7 != 0){
        	count += 1;
      }
    }
  }
  printf("Node: %d Rows: %d - %d\n", myRank, low, high);
  printf("%d count is: %ld\n", myRank, count);
  MPI_Finalize();
  return 0;
}
