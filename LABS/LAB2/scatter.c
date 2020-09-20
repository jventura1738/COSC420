#include<stdio.h> // printf
#include<mpi.h>
#include<unistd.h> // sleep
#include<stdlib.h> // rand, srand
#include<time.h>   // time
#include<string.h> // strcat

int main(int argc, char** argv){
  MPI_Init(&argc, &argv); // pass through cli args

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  // worldSize will be the total number of
  // nodes in the communicator.
  // myRank will be the nodes id within that
  // communicator
  int worldSize, myRank, i;

  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  if(argc < 2){
    printf("Usage: ./scatter N\n");
    MPI_Finalize();
    return 0;
  }

  srand(time(NULL) + myRank);

  int N = atoi(argv[1]);

  if( N % worldSize > 0 ){
    printf("Choose N divisible by %d\n", worldSize);
    MPI_Finalize();
    return 0;
  }

  double* arr = NULL;

  // only the root starts with all the data
  if (myRank == 0){
    // more realistically, would read in an
    // array from a large datafile, or something
    arr = malloc(N*sizeof(double));

    for(i=0; i<N; i++){
      arr[i] = (double)rand() / RAND_MAX; // 0 to 1
      printf("%0.2f ", arr[i]);
    }
    puts("");
  }

  // the chunk of the array that will be scattered to me
  // NB: beware of rounding issues!
  int local_len = N / worldSize;
  double* local_arr = malloc(local_len*sizeof(double));

  MPI_Scatter(
      arr, local_len, MPI_DOUBLE,         // send info
      local_arr, local_len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info

  char* buf = malloc(5*local_len + 1);
  memset(buf, 0, 5*local_len + 1);
  /* long way of doing above ^ with memset
  for(i=0; i< 5*local_len + 1; i++){
    buf[i] = 0;
  }
  */
  char tmp[6];
  for(i=0; i<local_len; i++){
    sprintf(tmp, "%0.2f ", local_arr[i]);
    strcat(buf, tmp);
  }

  printf("I am node %d and my numbers are %s\n", myRank, buf);

  free(local_arr);
  free(buf);
  if( myRank == 0 ){
    free(arr);
  }
  MPI_Finalize();
  return 0;
}










