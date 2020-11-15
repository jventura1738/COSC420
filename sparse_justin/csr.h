// Justin Ventura COSC420

#include "matrix.h"

#ifndef CSR_H
#define CSR_H

/*
 * COMPRESSED SPARSE ROW MATRIX STRUCT
 * 
 * This is going to be our way of representing
 * sparse matrices in order to save immense
 * amounts of time.  This is going to act like
 * a graph (since it is essentially an adj
 * list).
*/
typedef struct compressed_sparse_row {

    // Offsets for each "node."
    int * source_rows;

    // The actual matrix data.
    int * source_cols;

    // The actual values.
    double * source;

    // This keeps track of |E|, |V|.
    int nvertices;
    int nedges;

} csr_matrix;


/*
 * INITIALIZE CSR MATRIX FUNCTION
 * 
 * Allocates heap memory for the provided
 * csr_matrix.
*/
void set_csr(csr_matrix * graph, int * row_ptr, int * col_ptr, double * vals, int nv, int ne) {

    graph->nvertices = nv;
    graph->nedges = ne;
    graph->source_rows = (int*) malloc((graph->nvertices + 1) * sizeof(int));
    graph->source_cols = (int*) malloc((graph->nedges + 1) * sizeof(int));
    graph->source = (double*) malloc((graph->nedges + 1) * sizeof(double));

    int i;
    for(i = 0; i < nv + 1; i++) {

        graph->source_rows[i] = row_ptr[i];

    }

    for(i = 0; i < ne; i++) {

        graph->source_cols[i] = col_ptr[i];

    }

    for(i = 0; i < ne; i++) {

        graph->source[i] = vals[i];

    }

}


/*
 * SPARSE MATRIX TO CSR FORM CONVERTER
 * 
 * Given an N x N sparse matrix, this function
 * will convert it to compressed sparse row
 * form.
*/
void to_csr(matrix * A, csr_matrix * graph) {

    int row_ptrs[A->rows+1];
    int col_ptrs[(A->rows * A->rows) + 1];
    double vals[(A->rows * A->rows) + 1];
    int nv = A->rows;
    int ne = 0;

    int i, j;
    row_ptrs[0] = 0;
    for(i = 0; i < A->rows; i++) {

        for(j = 0; j < A->cols; j++) {

            int index = INDEX(A, i, j);

            if(A->data[index] != 0) {

                vals[ne] = A->data[index];
                col_ptrs[ne] = j;
                ne++;

            }
        }

        row_ptrs[i + 1] = ne;

    }

    set_csr(graph, row_ptrs, col_ptrs, vals, nv, ne);

}


/*
 * SPARSE MATRIX MULTIPLICATION FUNCTION
 * 
 * Given a csr_matrix (N x N) and a vector,
 * this will compute the product. This will
 * return a 1 x N vector.
*/
void csr_dot(csr_matrix * graph, double * v, double * final) {

    int i, j;
    // C is dumb sometimes
    // double * final = (double*) malloc(graph->nvertices * sizeof(double));

    for(i = 0; i < graph->nvertices; i++) {

        final[i] = 0.0;

        for(j = graph->source_rows[i]; j < graph->source_rows[i + 1]; j++) {

            final[i] += 1.0 * v[graph->source_cols[j]];

        }

    }

}


/*
 * PRINT CSR MATRIX FUNCTION
 * 
 * Prints CSR matrix-graph in a way so
 * that it can be viewed as an adjacency
 * list.
*/
void print_csr(csr_matrix * graph) {

    int i, j;
    for(i = 0; i < graph->nvertices; i++) {

        int low = graph->source_rows[i];
        int hi = graph->source_rows[i + 1];
        printf("%d -> ", i);

        for(j = low; j < hi; j++) {

            printf("%d ", graph->source_cols[j]);
            printf("(%f) ", graph->source[j]);

        }

        puts("");

    }

}


/*
 * CSR MATRIX TEST PRINT FUNCTION
 * 
 * Prints the offsets, then the actual data.
 * This is for debugging and testing.
*/
void test_print(csr_matrix * graph) {

    int i;
    for(i = 0; i < graph->nvertices+1; i++) {

        printf("%d  ", graph->source_rows[i]);

    }
    puts("");

    for(i = 0; i < graph->nedges; i++) {

        printf("%d  ", graph->source_cols[i]);

    }
    puts("");

    for(i = 0; i < graph->nedges; i++) {

        printf("%f  ", graph->source[i]);

    }
    puts("");

}


/*
 * CLEAR CSR MATRIX FUNCTION
 * 
 * Deallocates CSR matrix-graph.
*/
void clear_csr(csr_matrix * graph) {

    free(graph->source_rows);
    free(graph->source_cols);
    free(graph->source);

}

#endif
