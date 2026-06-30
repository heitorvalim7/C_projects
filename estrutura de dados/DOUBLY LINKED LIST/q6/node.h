#ifndef _NODE_H_
#define _NODE_H_

typedef int data_type;

typedef struct node
{
    data_type value;
    struct node *prev;
    struct node *next;
} node;


node *construct_node(data_type value, node *prev, node* next);


#endif