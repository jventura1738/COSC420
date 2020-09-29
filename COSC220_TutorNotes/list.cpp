#include "list.h"
#include <iostream>

/*
 * Function to create a node with a given value:
 * val.  Dynamically allocates a new node and
 * points
*/
Node * create_node(int val) {

    Node * rtn = new Node;
    rtn->data = val; // *(rtn.data) = val;
    rtn->next = nullptr;
    return rtn;

}

/*
 * Function to insert a node with a given value:
 * val, into a list that starts at head.  This
 * will insert the new node into a proper sorted
 * order.
*/
Node * insert_node(Node * head, int val) {

    Node * newnode = create_node(val);
    Node * curr = head;
    if (!head)
        return newnode;
    if (newnode->data < curr->data) {
        newnode->next = head;
        return newnode;
    }
    while(curr->next && newnode->data >= curr->next->data) {

        curr = curr->next;

    }
    newnode->next = curr->next;
    curr->next = newnode;
    return head;

}

/*
 * This is a function to print a list that
 * starts at head.
*/
void print_list(Node * head) {

    while(head) {

        std::cout << head->data << " ";
        head = head->next;

    }

    std::cout << "\n";

}
