#include <stddef.h>
#include <stdio.h>
#include "mpi.h"
#include <math.h>
long double divisor(long double n){
  long double i;
  long double sum = 0;
  for(i = 1; i <= sqrt(n); i++){
    if (fmod(n,i) == 0){
      if(n/i == i){
        sum += i*i;
      }else{
        sum += i*i;
        sum += (n/i)*(n/i);
      }
    }
      
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



  long double n = 64000000;
  long double Final_sum = 0;
  long double i, temp, sum;
  long double range, low, high;
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
  
  printf("Node: %d Numbers: %Lf - %Lf\n", myRank, low, high);
  printf("%d count is: %Lf\n", myRank, Final_sum);
  MPI_Reduce(&Final_sum, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, world);
  if(myRank == 0){
    printf("Sum: %Lf", sum);
  }
  MPI_Finalize();
  return 0;
}
