// Justin Ventura Serial Test File

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct {
  int rows, cols;
  double* data;
} matrix;

// Helpful functions.
void init_rand_matrix(matrix *, int, int);
void print_matrix(matrix *A);

/*
 * Serial Inner Product:
 * This is just for testing.
*/
double inner_prod(matrix *, matrix *);

/*
 * Matrix Transpose:
 * This is just for testing.
*/
matrix transpose(matrix *);

int main(int argc, char** argv) {

  srand(0);
  int i, j, k;

  matrix A, B, C;
  init_rand_matrix(&A, 3, 5);
  init_rand_matrix(&B, 5, 4);
  C.rows = 3;
  C.cols = 4;
  C.data = malloc(12 * sizeof(double));
  matrix Bt = transpose(&B);

  printf("Matrix A: \n");
  print_matrix(&A);
  printf("Matrix B: \n");
  print_matrix(&B);
  printf("Matrix Bt: \n");
  print_matrix(&Bt);
  puts("");

  matrix row_vect, col_vect;
  row_vect.rows = 1;
  row_vect.cols = A.cols;
  row_vect.rows = 1;
  row_vect.cols = A.cols;
  row_vect.data = malloc(A.cols * sizeof(double));
  col_vect.data = malloc(A.cols * sizeof(double));

  for (i = 0; i < A.cols; i++) {

    row_vect.data[i] = 0;
    col_vect.data[i] = 0;

  }

  /* ALG START */

  // Iterate the rows of A:
  for (i = 0; i < A.rows; i++) {

    // Iterate the rows of Bt:
    for (j = 0; j < Bt.rows; j++) {

      // Find the corresponding vectors:
      for (k = 0; k < A.cols; k++) {

        row_vect.data[k] = A.data[ i * A.cols + k];
        col_vect.data[k] = Bt.data[j * A.cols + k];

      }

      C.data[i * C.cols + j] = inner_prod(&row_vect, &col_vect);

    }

  }

  /* ALG END */ 

  printf("Resulting Matrix from A*B:\n");
  print_matrix(&C);

  return 0;
}

// Make a random Matrix.
void init_rand_matrix(matrix *A, int rows, int cols) {

  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows * A->cols * sizeof(double));

  int i;
  for(i = 0; i < A->rows* A->cols; i++) {

    A->data[i] = rand() % 10 + 1;

  }

}

// Print Matrix.
void print_matrix(matrix *A) {

  int i,j;

  for(i = 0; i < A->rows; i++) {

    for(j = 0; j < A->cols; j++) {

      printf("%0.2f ", A->data[i * A->cols + j]);

    }

    puts("");

  }

}

// Serial Inner Product.
double inner_prod(matrix * row_vect, matrix * col_vect) {

  int i;
  double sum = 0.0;

  for (i = 0; i < row_vect->cols; i++) {

    sum += row_vect->data[i] * col_vect->data[i];

  }

  return sum;

}

// Matrix Transpose
matrix transpose(matrix * A) {

  matrix At;
  At.rows = A->cols;
  At.cols = A->rows;
  At.data = malloc(A->rows * A->cols * sizeof(double));

  int i, j;

  for (int i = 0; i < A->cols; i++) {

		for (int j = 0; j < A->rows; j++) {

			At.data[i * A->rows + j] = A->data[j * A->cols + i];

		}
	
	}

  return At;

}