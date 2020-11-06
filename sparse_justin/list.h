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
 * <--------  MASTER NODE  -------->
 * 
 * This acts like a 'linked list' class
 * that keeps track of the a linked list.
*/
typedef struct {

    // Number of nodes in list.
    int count;

    // Keeps track of front and back.
    struct list_node * head;
    struct list_node * tail;

} master_node;


/*
 * <--------  LIST   NODE  -------->
 * 
 * This acts like a 'linked list' class
 * that keeps track of the a linked list.
*/
typedef struct {

    // ID of the research paper.
    int ID;

    // Points to the next node in the list.
    struct list_node * next;

} list_node;


list_node * init_node(int id) {

    list_node * new_node;
    new_node->ID = id;
    new_node->next = NULL;

    return new_node;

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
void append(master_node * master, int id) {

    if (in_list(master, id)) {

        return; // no duplicates allowed.

    }

    struct list_node * new_node = init_node(id);

    if (!master->head) {

        master->head = new_node;
        master->tail = new_node;
        master->count = 1;

    }
    else {

        list_node * temp = master->tail;
        master->tail = new_node;
        temp->next = new_node;
        master->count++;

    }

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
int in_list(master_node * master, int id) {

    if (!master->head) {

        // puts("Warning[ in_list() ]: list (master) is empty. (NULL)");
        return NULL;

    }
    else {

        list_node * temp = master->head;

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
 * PRINT LIST FUNCTION.
 * 
 * Prints the list (master) from head
 * to tail.  Provides newline.
*/
void print(master_node * master) {

    list_node * temp = master->head;
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

    }

}

#endif