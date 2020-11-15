/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h"  // linked list
#include "KWBST.h" // binary search tree for keywords

int main (int argc, char ** argv) {

    keyword_node * ROOT = NULL;
    ROOT = insert(ROOT, "matrices");
    append(ROOT->MASTER, 0);

    const int SIZE = 7;
    char * arr[7] = {"eigenvalue", "EIGENVALUE", "eigen vector", "linearly independent", "vector space", "gauss-jordan", "diagonal"};

    int i;
    for (i = 1; i <= SIZE; i++) {

        insert(ROOT, arr[i-1]);
        keyword_node * test = find(ROOT, arr[i-1]);
        append(test->MASTER, i);
        printf("-> %f to %s\n", test->MASTER->tail->ID, test->keyword);

    }

    in_order(ROOT);
    puts("");
    clear_tree(ROOT);

    return 0;
}
