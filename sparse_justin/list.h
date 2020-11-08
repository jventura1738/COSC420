/*
 * COSC420 arXiv list structure.
 * 
 * - Justin Ventura
*/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

/*
 * <--------  LIST   NODE  -------->
 * 
 * This acts like a 'linked list' class
 * that keeps track of the a linked list.
*/
typedef struct list_node {

    // ID of the research paper.
    int ID;

    // Points to the next node in the list.
    struct list_node * next;

} list_node;


/*
 * <--------  MASTER NODE  -------->
 * 
 * This acts like a 'linked list' class
 * that keeps track of the a linked list.
*/
typedef struct master_node {

    // Number of nodes in list.
    int count;

    // Keeps track of front and back.
    list_node * head, * tail;

} master_node;

/*
 * INIT MASTER NODE.
 * 
 * Initializes the master node.
*/
void init_master(master_node * master) {

    master = malloc(sizeof(master_node));
    master->count = 0;
    master->head = NULL;
    master->tail = NULL;

}

/*
 * INIT NODE FUNCTION.
 * 
 * Allocates a new node on the heap.
*/
list_node * init_node(int id) {

    list_node * new_node = malloc(sizeof(list_node));
    new_node->ID = id;
    new_node->next = NULL;

    return new_node;

}

/*
 * EXISTENCE CHECK FUNCTION.
 * 
 * Searches the list (master) for a node
 * with the id passed as parameter. This
 * will return 1 if found, 0 otherwise.
 * 
 * NOTE: returns NULL when empty.
*/
int in_list(list_node * head, int id) {

    if (!head) {

        //puts("Warning[ in_list() ]: list (master) is empty. (NULL)");
        return 0;

    }
    else {

        list_node * temp = head;

        while (temp) {

            if (temp->ID == id) {

                return 1;

            }

            temp = temp->next;

        }

    }

    return 0;

}

/*
 * APPEND FUNCTION
 * 
 * This function append a node with the
 * given id to the list (master).
 * 
 * NOTE: Automatically checks if this is
 * a duplicate.  Will not insert if this
 * is the case.
*/
void append(list_node * head, int id) {

    list_node * new_node = init_node(id);
    if (!new_node) {

        printf("Memory error: Could not append: %d.\n", id);

    }

    if (!head) {

        head = new_node;

    }
    else if (in_list(head, id) == 1) {

        return; // no duplicates allowed.

    }
    else {

        list_node * temp = head;
        while(temp->next) {

            temp = temp->next;

        }
        temp->next = new_node;

    }

}


/*
 * PRINT LIST FUNCTION.
 * 
 * Prints the list (master) from head
 * to tail.  Provides newline.
*/
void print(list_node * head) {

    list_node * temp = head;
    while(temp) {

        printf("%d ", temp->ID);
        temp = temp->next;

    }

    puts("");

}

/*
 * CLEAR LIST FUNCTION.
 * 
 * This function empties the list (master)
 * by deleting all elements.
*/
void clear(master_node * master) {

    list_node * temp = master->head;
    while(temp) {

        master->head = temp->next;
        free(temp);
        master->count--;
        temp = master->head;

    }

}

#endif