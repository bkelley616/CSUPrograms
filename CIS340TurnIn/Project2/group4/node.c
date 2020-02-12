
//Brandon Kelley 2716916 & Kyle Hoffman 2701222
//node.c(Defines the function insertsort and printlist, as declared in node.h.)

//include the proper libraries and header files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

//method to create a node
struct mynode* createNode (int inputValue){
    struct mynode *newCreatedNode;
    newCreatedNode = malloc(sizeof (struct mynode));
    struct mynode node = {inputValue,NULL,NULL};
    memcpy(newCreatedNode, &node, sizeof(struct mynode));
    return newCreatedNode;
}

//inserts a node a the tail of the list
struct mynode* insertNode (struct mynode * tail, int inputValue){
    struct mynode* newCreatedNode = createNode(inputValue); //create new node with input value

    //add the newly created node to the end of this list, it now becomes the tail
    tail->next = newCreatedNode;
    newCreatedNode->prev = tail;
    newCreatedNode->next = NULL;
    //printf("%d", (*head).value); //debug head & tail values
    //printf("%d", (*tail).value);

    return newCreatedNode;
}

//sorts the given list (provided by head pointer) and returns a pointer to the head of the sorted list
struct mynode * insertsort (struct mynode* linkedListHead){


    struct mynode* sortedHead = createNode(linkedListHead->value); //create sorted list head
    struct mynode * unsortedPointer = linkedListHead->next; //create pointer to maintain pointer to unsorted list
    struct mynode * sortedPointer = sortedHead;//set the sorted pointer to the head of sorted list

    while (unsortedPointer != NULL) { //while we are not at the end of the unsorted list

        //head case
        if(sortedPointer->value > unsortedPointer->value){ //if new sorted value is less than sorted value at head, then
           struct mynode* newNode = createNode(unsortedPointer->value); // place new value at the head of the sorted list
            newNode->next = sortedHead;                                 // and set the appropriate pointers
            sortedHead->prev = newNode;
            sortedHead = newNode;

        } else { // we will place the new sorted node in the middle or at the tail

            //find the place to insert
            while (sortedPointer->next != NULL &&  sortedPointer->next->value < unsortedPointer->value)
                sortedPointer = sortedPointer->next;

            //create new node to insert at the corresponding index
            struct mynode* newNode = createNode(unsortedPointer->value);

            //tail case
            if(sortedPointer->next == NULL){ //place node at the end of the sorted list and set proper links
                newNode->prev = sortedPointer;
                sortedPointer->next = newNode;
            } else { //middle case
                //place the node in the middle and set proper links
                sortedPointer->next->prev = newNode;
                newNode->next = sortedPointer->next;

                sortedPointer->next = newNode;
                newNode->prev =sortedPointer;
            }
        }
        unsortedPointer = unsortedPointer->next;// increment the unsorted pointer
        sortedPointer = sortedHead; //reset the sorted pointer back to the beginning of the sorted list
    }
    return sortedHead; // return the head of the newly created sorted doubly linked list
}

//traverses the doubly linked list and prints out each node
void printlist (struct mynode* linkedListHead) {
    while (linkedListHead != NULL) { //while not at end of list
        if ((*linkedListHead).next == NULL) //if this is the tail print out with different format
            printf("%d", linkedListHead->value);
        else
            printf("%d<==>", linkedListHead->value);

        linkedListHead = linkedListHead->next; //advance to next node
    }
}



