#include "node.h"
#include <stdio.h>
#include <stdlib.h>

Node *node_construct(data_type value, Node *prev, Node *next){
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->last = prev;
    n->next = next;
    n->value = value;

    return n;
}