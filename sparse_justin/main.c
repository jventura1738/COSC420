/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h" // linked list class

void init_master(master_node * master) {

    master->count = 0;
    master->head = NULL;
    master->tail = NULL;

}

int main (int argc, char ** argv) {

    puts("here");
    master_node MASTER;
    puts("here");
    // MASTER->head = NULL;
    // MASTER->tail = NULL;
    // MASTER->count = 0;
    init_master(&MASTER);

    puts("here");

    int i;
    for (i = 0; i < 10; i++) {

        puts("hereasldjflkasdjfklas");
        append(&MASTER, i);

    }

    puts("here");

    print(&MASTER);

    puts("here");
    clear(&MASTER);

    return 0;
}