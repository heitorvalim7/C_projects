#include "node.h"
#include <stdio.h>
#include <stdlib.h>


Node *node_construct(int item, Node *prev, Node *next){
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->next = next;
    n->prev = prev;
    n->value = item;

    return n;
}