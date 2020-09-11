// Justin Ventura & Blaine Mason
// COSC420 Lab 1: Lab-1-prime.c
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include <math.h>
#include <time.h> 

int main(int argc, char** argv){
  MPI_Init(&argc, &argv);
  MPI_Comm world = MPI_COMM_WORLD;	  
  
  int worldSize, myRank;
  
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);
 
  //Here we gather oue user input and define a buffer
  unsigned long int N = atoi(argv[1]);
  unsigned long int buffer = sqrt(N+1);
  int start, upper;

  //If the rank is the master node, it will begin at 2
  //and the upper bound is defined as the (start - 1) + sqrt(n)/p 
  //Else, start is found by the given equation then upper uses the same
  //technique.
  if(myRank == 0){
    start = 2;
    upper = (start-1) + (buffer/worldSize);
  }else{
    start = (myRank)*(buffer/worldSize) + 1;
    upper = start + (buffer/worldSize);
  }
  
  //If the N has a factor, print them and abort the program.
  int i;
  for(i = start; i < upper; i++){
    if(N % i == 0){
      printf("Not Prime! One Factor is %lu and %d\n", N/i, i);
      MPI_Abort(world, 0);
    }
  }

  MPI_Finalize();
  return 0;
}

