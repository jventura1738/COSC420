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
    for (i = 0; i < 3; i++) {

        puts("ITERATION");
        insert(ROOT, arr[i]);
        puts("inserting");
        keyword_node * test = find(ROOT, arr[i]);
        if (!test->MASTER) {

            test->MASTER = init_master();

        }
        puts("before");
        append(test->MASTER, i);
        puts("after");
        printf("ID: %d \n", test->MASTER->tail->ID);
        printf("kw: %s", test->keyword);
        printf("kw: %s, ID: %d \n", test->keyword, test->MASTER->tail->ID);
        printf("->%d to %s\n", test->MASTER->head->ID, test->keyword);

    }

    in_order(ROOT);
    puts("");

    return 0;
}