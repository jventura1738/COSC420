#include "matrix.h"
#define DIM 3
#define LIMIT 10
#define VERBOSE 0

void writeToFile(matrix *A, MPI_Comm world, int worldSize, int myRank){
  MPI_File fh;
  initRandMatrix(A, DIM, DIM);
  int * send_cnts = malloc(sizeof(int) * worldSize);
  int * disp_cnts = malloc(sizeof(int) * worldSize);
  int i, disp = 0;

  for (i = 0; i < worldSize; i++) {
    send_cnts[i] = (DIM * DIM)/worldSize;
    disp_cnts[i] = disp;
    disp += (DIM * DIM)/worldSize;
  }
  if ((DIM * DIM) % worldSize > 0) {
    send_cnts[worldSize-1] += (DIM*DIM) % worldSize;
  }

  double * local_m = malloc(sizeof(double) * send_cnts[myRank]); 
  MPI_Scatterv(A->data, send_cnts, disp_cnts, MPI_DOUBLE, local_m, send_cnts[myRank], MPI_DOUBLE, 0, world);
  MPI_Offset offset = myRank * sizeof(double) * send_cnts[myRank];
  // hexdump -v -e '5/4 "%3d"' -e '"\n"'  datafile
  MPI_File_open(world, "outfile",
      MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
  MPI_File_write_at(fh, offset, local_m, send_cnts[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);
  MPI_File_close(&fh);
  free(send_cnts);
  free(disp_cnts);
  free(local_m);

}

double* readFromFile(MPI_Comm world, int worldSize, int myRank){
  MPI_File fh;
  matrix temp;
  initMatrix(&temp, DIM, DIM);
  int * send_cnts = malloc(sizeof(int) * worldSize);
  int * disp_cnts = malloc(sizeof(int) * worldSize);
  int i, disp = 0;

  for (i = 0; i < worldSize; i++) {
    send_cnts[i] = (DIM * DIM)/worldSize;
    disp_cnts[i] = disp;
    disp += (DIM * DIM)/worldSize;
  }
  if ((DIM * DIM) % worldSize > 0) {
    send_cnts[worldSize-1] += (DIM*DIM) % worldSize; 
  }

  double * local_m = malloc(sizeof(double) * send_cnts[myRank]); 
  
  MPI_Offset offset = myRank * sizeof(double) * send_cnts[myRank];
  // hexdump -v -e '5/4 "%3d"' -e '"\n"'  datafile
  MPI_File_open(world, "Ax",
      MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

  MPI_File_read_at(fh, offset, local_m, send_cnts[myRank], MPI_DOUBLE, MPI_STATUS_IGNORE);
  //MPI_Scatterv(temp.data, send_cnts, disp_cnts, MPI_DOUBLE, local_m, send_cnts[myRank], MPI_DOUBLE, 0, world);
  MPI_File_close(&fh);

  MPI_Gatherv(local_m, send_cnts[myRank], MPI_DOUBLE, temp.data, send_cnts, disp_cnts, MPI_DOUBLE, 0, world);

  free(send_cnts);
  free(disp_cnts);
  free(local_m);

  return temp.data;

}
int main(int argc, char** argv) {

  srand(0);
  MPI_Init(&argc, &argv);

  // This constant gets set by the MPI lib
  MPI_Comm world = MPI_COMM_WORLD;

  // worldSize will be the total number of
  // nodes in the communicator.
  // myRank will be the nodes id within that
  // communicator.
  int worldSize, myRank;

  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &myRank);

  /* do work */

  // matrix A;
  // matrix e;
  // matrix gamer;
  matrix ree;
  // int z, count = 0, success = 0;
  // e.data = malloc(sizeof(double) * DIM);
  // e.rows = DIM;
  // e.cols = 1;
  // matrix x;
  // x.data = malloc(sizeof(double) * DIM);
  // x.rows = e.rows;
  // x.cols = e.cols;

  // for (z = 0; z < DIM; z++) {
    
  //   e.data[z] = 1;
  //   x.data[z] = 1;

  // }

  // initMatrix(&gamer, DIM, DIM);
  // writeToFile(&A, world, worldSize, myRank);
  // gamer.data  = readFromFile(world, worldSize, myRank);

  // if (myRank == 0) {

  //   puts("A:");
  //   printMatrix(&gamer);

  // }
  
  // while ((count < LIMIT) && !success) {

  //   // puts("x:");
  //   // printMatrix(&x);

  //   matrix temp;
  //   temp.rows = x.rows;
  //   temp.cols = x.cols;
  //   temp.data = x.data;

  //   x.data = multiplyMatrix(&gamer, &x, world, worldSize, myRank);
  //   double * new_x = normalize(&x, world, worldSize, myRank);
  //   x.data = new_x;

  //   MPI_Bcast(x.data, DIM, MPI_DOUBLE, 0, world);

  //   if (myRank == 0 && VERBOSE) {

  //     printf("x after pass %d:\n", count);
  //     int i;
  //     for (i = 0; i < DIM; i++) {

  //       printf("%f ", x.data[i]);

  //     }

  //     puts("");

  //   }

  //   double * test = subtractMatrix(&temp, &x, world, worldSize, myRank);
    
  //   MPI_Bcast(test, DIM, MPI_DOUBLE, 0, world);

  //   int i, sum = 0;
  //   for (i = 0; i < DIM; i++) {

  //     sum += test[i];

  //   }

  //   if (DIM - sum <= 0.000001) {
      
  //     success = 1;

  //   }

  //   free(test);

  //   count++;

  //   MPI_Barrier(world);
    
  // }

  // if (myRank == 0) {

  //   if (success) {

  //     puts("x:");
  //     printMatrix(&x);

  //   }
  //   else {

  //     puts("you suck, x:");
  //     printMatrix(&x);

  //   }

  // }

  /* end work */
  initMatrix(&ree, DIM, 1);


  matrix A;
  initMatrix(&A, DIM, DIM);
  writeToFile(&A, world, worldSize, myRank);

  ree.data = eigen_vector_file(DIM, world, worldSize, myRank);
  if(myRank == 0){
    printMatrix(&ree);
  }
  MPI_Barrier(world);

  // free(A.data);
  // free(e.data);
  // free(x.data);

  MPI_Finalize();

  return 0;
}