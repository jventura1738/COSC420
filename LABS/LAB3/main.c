/*
 * Justin Ventura & Blaine Mason
 * COSC420 Lab 3: Gauss Jordan
 *
 * Dr. Joe Timothy Anderson
*/
#include<mpi.h>
#include "matrix.h"
int main(int argc, char ** argv) {
  //srand(time(NULL));
  // MPI Business.
  MPI_Init(&argc, &argv);

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  int worldSize, myRank;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  // TODO: read from file to get matrix & vect.

  /*
  * Gauss-Jordan Elimination Algorithm.
  *
  * Performs the standard Gauss-Jordan
  * elimination algorithm for row reduction
  * in order to solve the linear system of
  *
  * -> Ax = b
  *
  * In  -> n*m Matrix A
  *        n*1 vector b
  *        MPI information.
  *
  * Out -> The solution vector "x".
  */

  // TODO: Perform alg.
  int n = 10;
  matrix A, b, aI, I, temp;
  matrix newb;
  initMatrix(&aI, n, n);
  initMatrix(&temp, n, n);
  initMatrix(&newb, n, 1);
  initRandMatrix(&A, n, n);
  initRandMatrix(&b, n, 1);
  initIMatrix(&I, n, n);
  if(myRank == 0){
    //printMatrix(&A);
    //printMatrix(&b);
  }

  newb.data = gauss_jordan(&A, &b, world, worldSize, myRank);

  if(myRank == 0){
    puts("");
    printf("The new b vector is:\n");
    printMatrix(&newb);
    puts("");
  }

  
  aI.data = gauss_jordan(&A, &I, world, worldSize, myRank);
  if(myRank == 0){
    printf("The A inverse:\n");
    printMatrix(&aI);
    puts("");
  }
  temp.data = multiplyMatrix(&A, &aI, world, worldSize, myRank);
  if(myRank == 0){
    printf("A*AI:\n");
    printMatrix(&temp);
    puts("");
  }
  


  /* File stuff for b*/
  MPI_File fh;

  int * send_cnts = malloc(sizeof(int) * worldSize);
  int * disp_cnts = malloc(sizeof(int) * worldSize);

  int i, disp = 0;
  for (i = 0; i < worldSize; i++) {

    send_cnts[i] = n/worldSize;
    disp_cnts[i] = disp;
    disp += n/worldSize;

  }
  if (n % worldSize > 0) {

    send_cnts[worldSize-1] += n % worldSize; 

  }

  double * local_m = malloc(sizeof(double) * send_cnts[myRank]);

  MPI_Scatterv(newb.data, send_cnts, disp_cnts, MPI_DOUBLE, local_m, send_cnts[myRank], MPI_DOUBLE, 0, world);
  MPI_Offset offset = myRank * sizeof(double) * send_cnts[myRank];


  // hexdump -v -e '5/4 "%3d"' -e '"\n"'  datafile

  MPI_File_open(world, "outfile1",
      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  MPI_File_write_at(fh, offset, local_m, send_cnts[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);

  MPI_File_close(&fh);

  free(send_cnts);
  free(disp_cnts);
  free(local_m);

  /* File stuff for AInv */

  send_cnts = malloc(sizeof(int) * worldSize);
  disp_cnts = malloc(sizeof(int) * worldSize);

  disp = 0;
  for (i = 0; i < worldSize; i++) {

    send_cnts[i] = n*n/worldSize;
    disp_cnts[i] = disp;
    disp += n*n/worldSize;

  }
  if (n*n % worldSize > 0) {

    send_cnts[worldSize-1] += n*n % worldSize; 

  }

  local_m = malloc(sizeof(double) * send_cnts[myRank]);

  MPI_Scatterv(aI.data, send_cnts, disp_cnts, MPI_DOUBLE, local_m, send_cnts[myRank], MPI_DOUBLE, 0, world);
  offset = myRank * sizeof(double) * send_cnts[myRank];


  // hexdump -v -e '5/4 "%3d"' -e '"\n"'  datafile

  MPI_File_open(world, "outfile2",
      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  MPI_File_write_at(fh, offset, local_m, send_cnts[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);

  MPI_File_close(&fh);

  free(send_cnts);
  free(disp_cnts);
  free(local_m);

  /* File stuff for A*IAnv */

  send_cnts = malloc(sizeof(int) * worldSize);
  disp_cnts = malloc(sizeof(int) * worldSize);

  disp = 0;
  for (i = 0; i < worldSize; i++) {

    send_cnts[i] = n*n/worldSize;
    disp_cnts[i] = disp;
    disp += n*n/worldSize;

  }
  if (n*n % worldSize > 0) {

    send_cnts[worldSize-1] += n*n % worldSize; 

  }

  local_m = malloc(sizeof(double) * send_cnts[myRank]);

  MPI_Scatterv(temp.data, send_cnts, disp_cnts, MPI_DOUBLE, local_m, send_cnts[myRank], MPI_DOUBLE, 0, world);
  offset = myRank * sizeof(double) * send_cnts[myRank];


  // hexdump -v -e '5/4 "%3d"' -e '"\n"'  datafile

  MPI_File_open(world, "outfile3",
      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  MPI_File_write_at(fh, offset, local_m, send_cnts[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);

  MPI_File_close(&fh);

  free(send_cnts);
  free(disp_cnts);
  free(local_m);

  MPI_Finalize();

  return 0;

}
