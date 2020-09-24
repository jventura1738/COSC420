
#include"matrix.h"
//Creates a random rxc matrix 
void initRandMatrix(matrix *A, int rows, int cols){
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      ACCESS(A,i,j) = rand() % 10 + 1;
    }
  }
}
//Creates a rxc matrix with 0 as the value
void initMatrix(matrix *A, int rows, int cols){
  int i,j;
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows*A->cols*sizeof(double));
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      ACCESS(A,i,j) = 0;
    }
  }
}
//Prints out the matrix
void printMatrix(matrix *A){
  int i,j;
  for(i=0; i < A->rows; i++){
    for(j=0; j < A->cols; j++){
      printf("%0.2f ", ACCESS(A,i,j));
    }
    puts("");
  }
}

double * addMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  
  if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;
    
  }
  int i;
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  for(i=0; i<worldSize; i++){
    sendcts[i] = len/worldSize; // number each gets
    displcmts[i] = i*(len/worldSize); // start indicies
  }

  if( len % worldSize > 0 ){
    int extra = len % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy
  }
  double* C = malloc(len*sizeof(double));
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));
  
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localA, len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localB, len, MPI_DOUBLE,   // recv info
      0, world); 
  for(i = 0; i < blockSize; i++) {
    localSoln[i] = localA[i] + localB[i];
  }
  
  MPI_Gatherv(localSoln, blockSize, MPI_DOUBLE, C, sendcts, displcmts, MPI_DOUBLE, 0, world);
  return C;

}

double * subtractMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
    if ( (A->rows != B->rows) || (A->cols != B->cols) ) {

    printf("Matrices not same dimension dummy boi.\n");
    return 0;
    
  }
  int i;
  int len = A->rows * A->cols;
  int blockSize = (len) / worldSize;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  for(i=0; i<worldSize; i++){
    sendcts[i] = len/worldSize; // number each gets
    displcmts[i] = i*(len/worldSize); // start indicies
  }

  if( len % worldSize > 0 ){
    int extra = len % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy
  }
  double* C = malloc(len*sizeof(double));
  double* localA = malloc(len*sizeof(double));
  double* localB = malloc(len*sizeof(double));
  double* localSoln = malloc(len*sizeof(double));
  
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localA, len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localB, len, MPI_DOUBLE,   // recv info
      0, world); 
  for(i = 0; i < blockSize; i++) {
    localSoln[i] = localA[i] - localB[i];
  }
  
  MPI_Gatherv(localSoln, blockSize, MPI_DOUBLE, C, sendcts, displcmts, MPI_DOUBLE, 0, world);
  return C;
}

double * multiplyMatrix(matrix *A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  if (A->cols != B->rows) {
		printf("matrices must have A.col == B.row");
    return 0;
	}
  if (worldSize > A->cols * B->rows) {
    printf("Just jokes....\n");
    return 0;
  }
  matrix Bt;
  Bt = transpose(B);
  int i, j, k;
  matrix row_vect, col_vect;
  row_vect.rows = 1;
  row_vect.cols = A->cols;
  row_vect.rows = 1;
  row_vect.cols = A->cols;
  row_vect.data = malloc(A->cols * sizeof(double));
  col_vect.data = malloc(A->cols * sizeof(double));
  for (i = 0; i < A->cols; i++) {

    row_vect.data[i] = 0;
    col_vect.data[i] = 0;

  }
  srand(time(NULL) + myRank);
  
  int len = A->rows*Bt.rows;
  double* final = malloc(len*sizeof(double));
  if (myRank == 0){
    for(i = 0; i < len; i++){
      
      final[i] = 0;
      
    } 
  }
  
  for(i=0; i < A->rows; i++){
    for(j=0; j < Bt.rows; j++){
        for(k= 0; k< A->cols; k++){
          row_vect.data[k] = ACCESS(A,i,k);
          col_vect.data[k] = Bt.data[j * A->cols + k];
          
        }
      final[INDEX(B,i,j)] = innerProduct(&row_vect, &col_vect, world, worldSize, myRank);
    }
  }
  
  return final;

	

}
double innerProduct(matrix* A, matrix *B, MPI_Comm world, int worldSize, int myRank){
  int size = A->cols;
  int i;
  int *sendcts = (int*) malloc(worldSize*sizeof(int));
  int *displcmts = (int*) malloc(worldSize*sizeof(int));

  for(i=0; i<worldSize; i++){
    sendcts[i] = size/worldSize; // number each gets
    displcmts[i] = i*(size/worldSize); // start indicies
  }

  if( size % worldSize > 0 ){
    int extra = size % worldSize;
    sendcts[worldSize-1] += extra; // small brain, easy
  }
  if(myRank == 0){
    int blockSize = ceil(size/worldSize);

  }
   
  double local_len = sendcts[myRank];
  double* localA = malloc(local_len*sizeof(double));
  double* localB = malloc(local_len*sizeof(double));
  
  MPI_Scatterv(
      A->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localA, local_len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info
  MPI_Scatterv(
      B->data, sendcts, displcmts, MPI_DOUBLE,// send info
      localB, local_len, MPI_DOUBLE,   // recv info
      0, world);                          // misc info

  int Final = 0;
  for(i = 0; i < local_len; i++){
    Final += localA[i] * localB[i];
  }

  int sum = 0;
  MPI_Reduce(&Final, &sum, 1, MPI_INT, MPI_SUM, 0, world);

  if (myRank == 0) {

    //printf("Inner Product: %d\n", sum);/

  }
  return sum;
}


matrix transpose(matrix* A){
  matrix At;
  At.rows = A->cols;
  At.cols = A->rows;
  At.data = malloc(A->rows * A->cols * sizeof(double));
  int i,j;

  for(i = 0; i < A->cols; i++){
    for(j = 0; j < A->rows; j++){
      At.data[i*A->rows + j] = ACCESS(A, j, i);  
    }
  }
    
  return At;
}

