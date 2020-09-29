/*
 * Justin Ventura COSC220 Tutor Notes.
 * Topic: Linked List Basics.
 * 
 * File: main.cpp
*/
#include<iostream>
#include"list.h"

int main() {

    int val = 1;
    //Node * head = create_node(val);

    Node * head = insert_node(nullptr, 5);
    head = insert_node(head, 1);
    head = insert_node(head, 4);
    head = insert_node(head, 6);

    for (int i = 0; i < 15; i++) {

        head = insert_node(head, i);

    }

    // should print:
    // 0 1 1 2 3 4 4 5 5 6 6 7 8 9 10 11 12 13 14
    print_list(head);

    return 0;
}