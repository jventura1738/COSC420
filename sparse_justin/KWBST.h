/*
 * COSC420 arXiv Binary Search Tree structure.
 * 
 * - Justin Ventura
*/

#ifndef KWBST_H
#define KWBST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * <--------  WORD   NODE  -------->
 * 
 * This will be a node that contains
 * a keyword as its key for a binary
 * search tree.
*/
typedef struct keyword_node {

    // assume 100 for now.
    char keyword[100];

    // These are the pointers for navigation.
    struct keyword_node * left, * right, * parent;

} keyword_node;


/*
 * INIT NODE FUNCTION.
 * 
 * Allocates a node on the heap.
*/
keyword_node * init_kwnode(char * word) {

    keyword_node * new_node = (keyword_node*) malloc(sizeof(keyword_node));
    strcpy(new_node->keyword, word);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;

}

/*
 * 
*/
void print(keyword_node * node) {

    printf("%s\n", node->keyword);

}

#endif