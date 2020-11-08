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
        test->head = append(test->head, i);
        printf("->%d \n", test->head->ID);

    }

    puts("gamer:");
    in_order(ROOT);
    puts("");

    // list_node * head = init_node(0);
    // for (i = 0; i < 5; i++) {

    //     append(head, i);

    // }

    // print(head);
    // clear(head);

    return 0;
}