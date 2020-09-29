#ifndef LIST_H
#define LIST_H

struct Node {
    int data;
    Node * next;
};

Node * create_node(int val);
Node * insert_node(Node * head, int val);
void print_list(Node * head);

#endif