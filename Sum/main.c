#include <stddef.h>
#include <stdio.h>
#include "mpi.h"
#include <math.h>
long double divisor(long double n){
  long double i;
  long double sum = 0;
  for(i = 1; i <= n; i++){
    if (fmod(n,i) == 0)
      sum += i*i;
  }
  return sum;
}
int main(int argc, char** argv){
  MPI_Init(&argc, &argv); // pass through cli args
  int worldSize, myRank;

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank); 



  long double n = 1000000;
  long double Final_sum = 0;
  long double i, temp;

  int range, low, high;
  range = n/worldSize;
  if(myRank == 0){
    low = 1;
    high = low + range;
  }else{
    low = myRank*range;
    high = low + range;
  }



  for(i = low; i <= high; i++){
    temp = sqrtl(divisor(i));
    if(temp - floor(temp) == 0){
      Final_sum += i;
    }
  }
  printf("Node: %d Numbers: %d - %d\n", myRank, low, high);
  printf("%d count is: %Lf\n", myRank, Final_sum);
  MPI_Finalize();
  return 0;
}
