/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h"  // linked list
#include "KWBST.h" // binary search tree

int main (int argc, char ** argv) {

    keyword_node * ROOT = init_kwnode("hi");
    char * arr[3] = {"eigenvalue", "inverse", "EIGENVALUE"};

    int i;
    for (i = 0; i < 6; i++) {

        puts("ITERATION");
        keyword_node * test = insert(ROOT, arr[i]);
        puts("1");
        if (test->MASTER == NULL) {

            puts("pre");
            init_master(test->MASTER);

        }
        puts("2");
        append(test->MASTER, i);

    }

    in_order(ROOT);
    puts("");

    // master_node MASTER;
    // init_master(&MASTER);

    // for (i = 0; i < 10; i++) {

    //     append(&MASTER, i);

    // }

    // print(&MASTER);
    // clear(&MASTER);

    return 0;
}