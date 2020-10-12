// Justin Ventura 10/09/20
// COSC420: Euclid

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

size_t gcd(size_t a, size_t b, size_t * count) {

  // (*count)++;
  // if (b > a) {

  //   return gcd(b, a, count);

  // }
  // else if (a % b == 0) {

  //   return b;

  // }
  // // a = b * q + r
  // else {

  //   size_t q = 1, r = 0;
  //   while (b * (q + 1) < a) {

  //     q++;

  //   }

  //   while (b * q + r < a) {

  //     r++;

  //   }

  //   if (r == 0) {

  //     printf("returning q=%zu. \n", q);

  //     return q;

  //   }
  //   else {

  //     return gcd(b, r, count);

  //   }

  // }

  (*count)++;
  if (a == 0) 
    return b;

  return gcd(b % a, a, count);

}

int main(int argc, char** argv) {

  size_t i, j, sum = 0, count = 0;
  size_t N = 5000000;

  MPI_Init(&argc, &argv); 
  int worldSize, myRank;

  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  size_t range, extra, low, high;
  size_t Final_sum = 0;

  MPI_File fh;
  size_t offset = myRank*sizeof(size_t);

  range = N / worldSize;
  extra = N % worldSize;
  if(myRank == 0){
      low = 1;
      high = low + range-2;
      //printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
  }else{
      if(myRank == (worldSize - 1)){
          low = (myRank*range);
          high = low + range + extra;
          //printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
      }else{
          low = (myRank*range);
          high = low + range -1;
          //printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
      }
  }   

  for (i = 1; i <= N; i++) {

    printf("iter: %zu\n", i);

    for (j = low; j <= high; j++) {

      gcd(i, j, &count);
      sum += count;
      count = 0;

    }

  }
  printf("Node %d finished with sum =  %zu.\n", myRank, sum);

  MPI_File_open(world, "datafile",
      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  printf("Rank: %d, Offset: %zu bytes.\n", myRank, offset);

  /* NEW VERSION */
  MPI_File_set_view(fh, offset, MPI_UNSIGNED_LONG_LONG, MPI_UNSIGNED_LONG_LONG, "native", MPI_INFO_NULL);
  MPI_File_write(fh, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_STATUS_IGNORE);

  MPI_Reduce(&sum, &Final_sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, world);

  if (myRank == 0) {

    printf("S(5000000)=%zu.\n", Final_sum - N*N);
    size_t result = Final_sum - N*N;
    MPI_File_write_at(fh, offset + worldSize, &result, 1, MPI_UNSIGNED_LONG_LONG, MPI_STATUS_IGNORE);

  }

  MPI_File_close(&fh);
  MPI_Finalize();

  return 0;

}
