#include "deque.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

struct Deque{
    node *last;
    node *head;
    int size;
};

Deque *deque_construct(){
    Deque *d = (Deque*)calloc(1, sizeof(Deque));
    d->head = NULL;
    d->last = NULL;
    d->size = 0;

    return d;
}
void deque_push_back(Deque *f, int item){
    node *new_node = construct_node(item, f->last, NULL);
    if(f->last == NULL){
        f->head = new_node;
        f->last = new_node;
    } else {
        f->last->next = new_node;
        f->last = new_node; 
    }
    f->size++;
}
void deque_push_front(Deque *f, int item){
    node *new_node = construct_node(item, NULL, f->head);
    if(f->head == NULL){
        f->head = new_node;
        f->last = new_node;
    } else{
        f->head->prev = new_node;
        f->head = new_node;
    }
    f->size++;
}
int deque_pop_back(Deque *f){
    if(f->last == NULL){
        return -1;
    }
    node *remove = f->last;
    data_type value= remove->value;
    f->last = f->last->prev;
    if(f->last != NULL){
        f->last->next = NULL;
    }
    free(remove);
    f->size--;
    if(f->size == 0){
        f->head = NULL;
    }
    return value;
}
int deque_pop_front(Deque *f){
    if(f->head == NULL){
        return -1;
    }
    node *remove = f->head;
    data_type data = remove->value;
    f->head = f->head->next;
    if(f->head != NULL){
        f->head->prev = NULL;
    }
    free(remove);
    f->size--;
    if(f->size == 0){
        f->last = NULL;
    }
    return data;
}
void deque_destroy(Deque *f){
    node *current = f->head;
    while(current != NULL){
        node *next = current->next;
        free(current);
        current = next;
    }
    free(f);
}