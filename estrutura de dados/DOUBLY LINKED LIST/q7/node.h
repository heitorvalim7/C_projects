#ifndef _NODE_H_
#define _NODE_H_


typedef int data_type;

typedef struct Node{
    struct Node *prev;
    struct Node *next;
    int value;
}Node;

Node *node_construct(int item, Node *prev, Node *next);

#endif