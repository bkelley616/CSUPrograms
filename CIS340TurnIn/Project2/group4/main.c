//Brandon Kelley 2716916 & Kyle Hoffman 2701222
//main.c(Handles input and output, as well as top-level program logic.)

//include the proper libraries and header files
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//declare head and tail pointers for unsorted doubly linked list and head node for sorted linked list
struct mynode* head = NULL;
struct mynode* tail = NULL;
struct mynode* sortedHead = NULL;

//main logic of program
int main() {
    //declare user input or value from redirected input file as int variable
    int nodeValue;

    //formatting
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\tProject 2: Linked List Before and After Insertion Sort ");
    printf("\n\n\n\tPlease Enter Each Node of the Linked List:\n\n");

    //while loop to take input from user or file, also sets head and tail accordingly
    while (1){
        printf("\t\t");
        scanf("%d", &nodeValue);
        //printf("\n%d",nodeValue); //debug to see if it is storing values

        if (nodeValue == 0) //stop receiving data if user or file enters 0
            break;

        if (head == NULL) { //if head null, then the list is empty so initialize the head and tail
            head = createNode(nodeValue);
            tail = head;
        } else { //else add a node at the end and update the tail reference
            tail = insertNode(tail,nodeValue);
        }
    }

    //check if list is empty, if so exit
    if(head == NULL) {
        printf("\n\n\tError: Doubly Linked List is Empty\n\n");
        printf("-------------------------------------------------------------------------------------------------------\n\n");
        exit(0);
    }

    //print the unsorted list
    printf("\n\n\tThe Unsorted Doubly Linked List is:\n\n\t\t");
    printlist(head);
    //printf("length: %d",length(head)); //debug length value


    printf("\n\n\n\tPerforming Insertion Sort...\n\t\t");
    sortedHead = insertsort(head); //sort the list using method in node.c and pass in head pointer as argument


    printf("\n\n\tThe sorted Doubly Linked List is:\n\n\t\t");
    printlist(sortedHead); //print out the sorted list by passing in sortedHead pointer as argument

    //formatting and end of program
    printf("\n\n-------------------------------------------------------------------------------------------------------\n\n");
    return 0;
}