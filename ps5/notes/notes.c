#include <stdio.h>
#include <stdlib.h>

// notes
/*
queue - FIFO (first in first out) - just like a line 1 --> 2 --> 3 - enqueue / dequeue
stack - LIFO (last in first out) - 3 --> 2 --> 1 - email inbox is an example (last email is at the top) - push / pop
// Queue
typedef struct
{
    person people[50];
    int size;
} queue;

// Stack
typedef struct
{
    person people[50];
    int size
} stack;

Appending in C
    no .append() method like python; annoying bc you have to worry about memory

Data structures are just clever ways of arranging memory

Linked list
    bunch of random bits that are stored as: data1 --> pointer to data2 --> data2 --> pointer to data3... --> NULL
    data + pointer combo stored as a node
    node: data & pointer (metadata) to next piece of data

atoi() converts string to int (ascii to int)

Trees
    doubly linked list
    left node and right node

Hashing
    taking a lot of inputs and mapping them to a finite (usually smaller) number of outputs
    Big O(n / k) instead of Big O(n) which makes a difference in the real world
    Can get to O(1) if you prioritize time over space
        best hash functions are somewhere in between
        most real world hash functions use fancy math to get very close to O(1)
    Tree of linked lists

Tries
    short for retrieval
    tree of arrays
    Arrays that point to each other essentially
    Always O(1)
    Not used as much as hash table because in every node you have 25 unused pointers

*/

int main(void)
{
    // appending an array
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list); // freeing original list
        return 1;
    }
    // now copy list --> tmp
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4; // adding last num

    free(list); // no need for list anymore
    list = tmp; // now we can just refer to tmp as list

    // implementing a node
    typedef struct node { // have to say node up here b/c you use it before you officially define node
        int number;
        struct node *next;
    } node;

    node *linked_list = NULL; // beginning of linked list
    node *n = malloc(sizeof(node));
    // (*n).number = 1; // making the data at n = 1
    n -> number = 1; // easier way to write (*n).number = 1
    n -> next = NULL; // end of linked list
    linked_list = n; // now, linked_list is a linked list of size one

    node *m = malloc(sizeof(node)); // second node
    m -> number = 2;
    m -> next = linked_list; // memory address of original node (1)
    linked_list = m;
    node *ptr = linked_list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr -> number);
        ptr = ptr -> next;
    }

    // binary search tree
    typedef struct treenode
    {
        int number;
        struct treenode *left; // don't want to just point to one node, want to point to left tree & right tree
        struct treenode *right;
    } treenode;

    // hash table
    typedef struct hashnode
    {
        char *name;
        char *number;
        struct hashnode *next;
    } hashnode;

    // try
    typedef struct trynode
    {
        struct trynode *children[26];
        char *number;
    } trynode;

    return 0;
}
