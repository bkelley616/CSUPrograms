
//Brandon Kelley 2716916 & Kyle Hoffman 2701222
//node.h(Declares the data structure and function insertsort, which sorts a given doubly linked list with
// the ascending order), and printlist, which prints a linked list to the screen.

#ifndef NODE_H
#define NODE_H

//Given data structure from assignment
struct mynode {
    int  const value; //will be constant for data file
    struct mynode *next;
    struct mynode *prev;
};

//method to create a node with the data structure provided above
extern struct mynode* createNode (int inputValue);


//The function insertsort must be declared exactly as follows.
//return value: struct mynode *.
//argument (only one): struct mynode *, which is the head of the given linked list.
extern struct mynode * insertsort (struct mynode* linkedListHead);
//does an insertion sort on the unsorted Doubly Linked List to produce sorted version

//The function printlist must be declared exactly as follows.
//return value: void.
//argument (only one): struct mynode *, which is the head of the given linked list.
extern void printlist (struct mynode* linkedListHead);
//prints a doubly linked list

//inserts a node at the end (tail)
extern struct mynode * insertNode (struct mynode * tail, int inputValue);

#endif //PROJECT2_NODE_H
