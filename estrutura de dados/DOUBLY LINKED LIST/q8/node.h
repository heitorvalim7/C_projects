#ifndef _NODE_H_
#define _NODE_H_

typedef int data_type;

typedef struct Node{
    struct Node *next;
    struct Node *last;
    data_type value;
}Node;

Node *node_construct(data_type value, Node *prev, Node *next);


#endif