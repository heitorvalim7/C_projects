#include "node.h"
#include <stdio.h>
#include <stdlib.h>


node *construct_node(data_type value, node *prev, node* next){
    node *n = (node*)calloc(1, sizeof(node));
    n->next = next;
    n->prev = prev;
    n->value = value;

    return n;
}