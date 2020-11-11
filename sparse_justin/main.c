/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h"   // linked list
#include "KWBST.h"  // binary search tree for keywords
#include "matrix.h" // matrix for floats

int main (int argc, char ** argv) {

    matrix adj;
    int N = 10;
    initMatrix(&adj, N, N);
    file_load_adj("test.txt", N, &adj);
    printMatrix(&adj);
    puts("");

    return 0;
}
