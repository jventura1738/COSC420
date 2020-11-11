/*
 * COSC420 arXiv list structure.
 * 
 * - Justin Ventura
*/

#ifndef WLIST_H
#define WLIST_H

#include <stdio.h>
#include <stdlib.h>

/*
 * <--------  LIST   NODE  -------->
 * 
 * This acts like a 'linked list node'
 * that keeps track of the ID of the word.
*/
typedef struct wlist_node {

    // ID of the research paper.
    char*  word;

    // Points to the next node in the list.
    struct wlist_node * next;

} wlist_node;

/*
 * <--------  MASTER NODE  -------->
 * 
 * This acts like a 'linked list' class
 * that keeps track of the a linked list.
*/
typedef struct wmaster_node {

    // Pointers to the head and tail of the linked list.
    wlist_node * head;
    wlist_node * tail;

    // Count of nodes.
    int node_count;

} wmaster_node; 


/*
 * INIT MASTER FUNCTION
 * 
 * Allocates a new master node on the heap.
*/
wmaster_node * winit_master() {
    
    wmaster_node * master = (wmaster_node*) malloc(sizeof(wmaster_node));
    master->head = NULL;
    master->tail = NULL;
    master->node_count = 0;

    return master;

}

/*
 * INIT NODE FUNCTION.
 * 
 * Allocates a new node on the heap.
*/
wlist_node * winit_node(char*  word) {

    wlist_node * new_node = malloc(sizeof(wlist_node));
    new_node->word = word;
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
int win_list(wmaster_node * master, char*  word) {

    if (!master->head) {

        //puts("Warning[ in_list() ]: list (master) is empty. (NULL)");
        return 0;

    }
    else {

        wlist_node * temp = master->head;

        while (temp) {

            if (temp->word == word) {

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
void wappend(wmaster_node * master, char*  word) {

    wlist_node * new_node = winit_node(word);
    if (!new_node) {

        printf("Memory error: Could not append: %s.\n", word);

    }
    if (!master) {
        master = winit_master();
    }
    if (!master->head) {

        master->head = new_node;
        master->tail = new_node;
        return;

    }
    else if (win_list(master, word)) {

        return;

    }
    else {

        wlist_node * temp = master->tail;
        master->tail = new_node;
        temp->next = new_node;
        master->node_count++;

    }

}


/*
 * PRINT LIST FUNCTION.
 * 
 * Prints the list (master) from head
 * to tail.  Provides newline.
*/
void wprint(wmaster_node * master) {

    wlist_node * temp = master->head;

    while(temp) {

        printf("%s\n", temp->word);
        temp = temp->next;

    }

}


/*
 * CLEAR LIST FUNCTION.
 * 
 * This function empties the list (master)
 * by deleting all elements.
*/
void wclear_list(wmaster_node * master) {

    wlist_node * temp = master->head;

    while(temp) {

        master->head = temp->next;
        free(temp);
        temp = master->head;

    }

}

#endif