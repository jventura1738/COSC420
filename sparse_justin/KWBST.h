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
#include "list.h"

/*
 * <--------  WORD   NODE  -------->
 * 
 * This will be a node that contains
 * a keyword as its key for a binary
 * search tree.
*/
typedef struct keyword_node {

    // Assume 100 for now.
    char keyword[100];

    // List to all papers this is referenced
    master_node * MASTER;

    // These are the pointers for navigation.
    struct keyword_node * left, * right;

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

    return new_node;

}

/*
 * INSERT NODE FUNCTION
 * 
 * Insert a node into the BST with the given key.
*/
keyword_node * insert(keyword_node * root, char * word) {

    if (!root) {

        return init_kwnode(word);

    }

    // Otherwise, recur down the tree
    if (strcasecmp(word, root->keyword) < 0) {

        root->left = insert(root->left, word);

    }
    else if (strcasecmp(word, root->keyword) > 0) {

        root->right = insert(root->right, word);

    }
 
    // return the (unchanged) node pointer
    return root;

}


/*
 * PRE-ORDER PRINT.
 * 
 * Print in pre-order (NLR).
*/
void pre_order(keyword_node * root) {

    if (root) {

        printf("%s ", root->keyword);
        pre_order(root->left);
        pre_order(root->right);

    }

}

/*
 * IN-ORDER PRINT.
 * 
 * Print in in-order (LNR).
*/
void in_order(keyword_node * root) {

    if (root) {

        in_order(root->left);
        printf("%s ", root->keyword);
        in_order(root->right);

    }

}

/*
 * POST-ORDER PRINT.
 * 
 * Print in POST-order (LRN).
*/
void post_order(keyword_node * root) {

    if (root) {

        post_order(root->left);
        post_order(root->right);
        printf("%s ", root->keyword);

    }

}

#endif