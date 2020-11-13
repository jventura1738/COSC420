/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h"   // linked list
#include "KWBST.h"  // binary search tree for keywords
#include "matrix.h" // matrix for floats
#include "csr.h"    // compressed sparse row form
#include "hits.h"   // hyper-text induced topic search


int main (int argc, char ** argv) {

    matrix adj;
    int N = 10;
    initMatrix(&adj, N, N);

    file_load_adj("test.txt", N, &adj);
    printMatrix(&adj);
    puts("");

    csr_matrix Graph;
    puts("----------------------------");
    to_csr(&adj, &Graph);
    test_print(&Graph);
    puts("----------------------------");
    print_csr(&Graph);

    float * hubs = (float*) malloc(Graph.nvertices * sizeof(float));
    float * auths = (float*) malloc(Graph.nvertices * sizeof(float));

    hits_alg(&Graph, hubs, auths);

    int i;
    for (i = 0; i < Graph.nvertices; i++) {

        printf("%f ", hubs[i]);

    }
    puts("\n");
    for (i = 0; i < Graph.nvertices; i++) {

        printf("%f ", auths[i]);

    }
    puts("");

    puts("thank the lord");

    return 0;
}
