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
 * INSERT NODE FUNCTION
 * 
 * Insert a node into the BST with the given key.
*/
keyword_node * insert(keyword_node * root, char * word) {
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
 
    /* return the (unchanged) node pointer */
    return node;

}

/*
 * PRE-ORDER PRINT.
 * 
 * Print in pre-order (NLR).
*/
void pre_order(keyword_node * root) {

    if (root) {

        printf("%d ", root->keyword);
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
        printf("%d ", root->keyword);
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
        printf("%d ", root->keyword);

    }

}

#endif