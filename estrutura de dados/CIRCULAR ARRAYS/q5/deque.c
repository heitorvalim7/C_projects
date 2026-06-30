#include "deque.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Deque{
    int *arr;
    int front;
    int back;
    int size;
    int capacity;
};

Deque *deque_construct(){
    Deque *d = (Deque*)calloc(1, sizeof(Deque));
    d->arr = (int*)calloc(10, sizeof(int));
    d->front = 0;
    d->back = 0;
    d->size = 0;
    d->capacity = 10;

    return d;
}
void deque_push_back(Deque *f, int item){
    if(f->size == f->capacity){
        int new_capacity = f->capacity * 2;
        int *new_arr = (int*)calloc(new_capacity, sizeof(int));
        for(int i = 0; i<f->size; i++){
            new_arr[i] = f->arr[(f->front + i) % f->capacity];
        }
        free(f->arr);
        f->arr = new_arr;
        f->front = 0;
        f->back = f->size;
        f->capacity = new_capacity;
    }
    f->arr[f->back] = item;
    f->back = (f->back + 1) % f->capacity;
    f->size++;

}
void deque_push_front(Deque *f, int item){
    if(f->size == f->capacity){
        int new_capacity = f->capacity * 2;
        int *new_arr = (int*)calloc(new_capacity, sizeof(int));
        for(int i = 0; i<f->size; i++){
            new_arr[i] = f->arr[(f->front + i) % f->capacity];
        }
        free(f->arr);
        f->arr = new_arr;
        f->front = 0;
        f->back = f->size;
        f->capacity = new_capacity;
    }
    f->front = (f->front - 1 + f->capacity) % f->capacity;
    f->arr[f->front] = item;
    f->size++;
}
int deque_pop_back(Deque *f){
    if(f->size == 0){
        return -100000;
    }
    f->back = (f->back - 1 + f->capacity) % f->capacity;
    int item = f->arr[f->back];
    f->size--;

    return item;
}
int deque_pop_front(Deque *f){
    if(f->size == 0){
        return -100000;
    }
    int item = f->arr[f->front];
    f->front = (f->front + 1) % f->capacity;
    f->size--;

    return item;

}
int deque_get(Deque *f, int idx){
    if(idx < 0 || idx >= f->size){
        return -100000;
    }
    return f->arr[(f->front + idx) % f->capacity];
}
void deque_destroy(Deque *f){
    free(f->arr);
    free(f);
}