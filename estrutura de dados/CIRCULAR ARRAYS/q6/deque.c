#include "deque.h"
#include <stdlib.h>
#include <string.h>

struct Deque{
    void **arr;
    int front;
    int back;
    int size;
    int capacity;
};

Deque *deque_construct(){
    Deque *d = (Deque*)calloc(1, sizeof(Deque));
    d->arr = (void**)calloc(10, sizeof(void*));
    d->front = 0;
    d->back = 0;
    d->size = 0;
    d->capacity = 10;

    return d;
}
void deque_push_back(Deque *d, void* item){
    if(d->size == d->capacity){
        int new_capacity = d->capacity * 2;
        void **new_arr = (void**)calloc(new_capacity, sizeof(void*));
        for(int i = 0; i<d->size; i++){
            new_arr[i] = d->arr[(d->front + i) % d->capacity];
        }
        free(d->arr);
        d->arr = new_arr;
        d->front = 0;
        d->back = d->size;
        d->capacity = new_capacity;
    }
    d->arr[d->back] = item;
    d->back = (d->back + 1) % d->capacity;
    d->size++;
}
void deque_push_front(Deque *d, void* item){
    if(d->size == d->capacity){
        int new_capacity = d->capacity * 2;
        void **new_arr = (void**)calloc(new_capacity, sizeof(void*));
        for(int i = 0; i<d->size; i++){
            new_arr[i] = d->arr[(d->front + i) % d->capacity];
        }
        free(d->arr);
        d->arr = new_arr;
        d->front = 0;
        d->back = d->size;
        d->capacity = new_capacity;
    }
    d->front = (d->front - 1 + d->capacity) % d->capacity;
    d->arr[d->front] = item;
    d->size++;
}
void* deque_pop_back(Deque *f){
    if(f->size == 0) return NULL;
    f->back = (f->back - 1 + f->capacity) % f->capacity;
    void *item = f->arr[f->back];
    f->size--;

    return item;
}

void* deque_pop_front(Deque *f){
    if(f->size == 0) return NULL;
    void *item = f->arr[f->front];
    f->front = (f->front + 1) % f->capacity;
    f->size--;
    return item;
}

void deque_destroy(Deque *f){
    free(f->arr);
    free(f);
}
