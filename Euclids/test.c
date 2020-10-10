// Justin Ventura 10/09/20
// COSC420: Euclid

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

size_t gcd(size_t a, size_t b, size_t * count) {

  *count++;
  if (b > a) {

    return gcd(b, a, count);

  }
  else if (a % b == 0) {

    return a / b;

  }
  // a = b * q + r
  else {

    size_t q = 1, r = 0;
    while (b * q < a) {

      q++;

    }

    while (b * q + r < a) {

      r++;

    }

    if (r == 0) {

      return q;

    }
    else {

      return gcd(b, r, count);

    }

  }

}

int main(int argc, char** argv) {

  size_t a = 6, b = 10, count = 0;
  size_t result = gcd(a, b, count);
  printf("GCD(%zu, %zu)=%zu.  Steps taken: %zu.\n", a, b, result, *count);

  return 0;

  // MPI_Init(&argc, &argv); 
  // int worldSize, myRank;

  // MPI_Comm world = MPI_COMM_WORLD;
  // MPI_Comm_size(world, &worldSize);
  // MPI_Comm_rank(world, &myRank);

  // long int i, j, k, range, extra, low, high;
  // long int n = 100;
  // long int sum = 0;
  // long int Final_sum = 0;
  // long int* mdrs = malloc(n*sizeof(long int));

  // range = n / worldSize;
  // extra = n % worldSize;
  // if(myRank == 0){
  //     low = 2;
  //     high = low + range-2;
  //     printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
  // }else{
  //     if(myRank == (worldSize - 1)){
  //         low = (myRank*range);
  //         high = low + range + extra;
  //         printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
  //     }else{
  //         low = (myRank*range);
  //         high = low + range;
  //         printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
  //     }
  // }   

  // MPI_Finalize();

  return 0;

}