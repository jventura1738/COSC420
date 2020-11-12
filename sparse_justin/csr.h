// Justin Ventura COSC420

#include "matrix.h"

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
    int * node_offsets;

    // The actual matrix data.
    int * source_indices;

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
void set_csr(csr_matrix * graph, int * dest, int * source, int nv, int ne) {

    graph->nvertices = nv;
    graph->nedges = ne;
    graph->node_offsets = (int*) malloc((graph->nvertices + 1) * sizeof(int));
    graph->source_indices = (int*) malloc((graph->nedges + 1) * sizeof(int));

    int i;
    for(i = 0; i < nv + 1; i++) {

        graph->node_offsets[i] = dest[i];

    }

    for(i = 0; i < ne; i++) {

        graph->source_indices[i] = source[i];

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

    int node[A->rows+1];
    int source[(A->rows * A->rows) + 1]; // max edges is n*n
    int nv = A->rows;
    int ne = 0;

    int i, j;
    node[0] = 0;
    for(i = 0; i < A->rows; i++){

        for(j = 0; j < A->cols; j++){

            int index = INDEX(A,i,j);
            if(A->data[index] != 0) {

                source[ne] = j; //hold index of which connected node
                ne++;

            }
        }

        node[i + 1] = ne;

    }

    set_csr(graph, node, source, nv, ne);

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

        int lowerBound = graph->node_offsets[i];
        int upperBound = graph->node_offsets[i+1];
        printf("%d -> ", i);
        for(j = lowerBound; j < upperBound; j++) {

            printf("%d ", graph->source_indices[j]);

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

    int i, j;
    for(i = 0; i < graph->nvertices+1; i++) {

        printf("%d  ", graph->node_offsets[i]);

    }

    puts("\n");
    for(i = 0; i < graph->nedges; i++) {

        printf("%d  ", graph->source_indices[i]);

    }

    puts("");

}


/*
 * CLEAR CSR MATRIX FUNCTION
 * 
 * Deallocates CSR matrix-graph.
*/
void clear_csr(csr_matrix * graph) {

    free(graph->node_offsets);
    free(graph->source_indices);

}