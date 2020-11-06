/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h" // linked list class

void init_master(master_node * master) {

    //master = malloc(sizeof(master_node));
    master->count = 0;
    master->head = NULL;
    master->tail = NULL;

}

int main (int argc, char ** argv) {

    master_node MASTER;
    init_master(&MASTER);

    int i;
    for (i = 0; i < 10; i++) {

        append(&MASTER, i);

    }

    print(&MASTER);
    clear(&MASTER);

    return 0;
}