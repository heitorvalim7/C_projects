#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Deque{
    int* data;
    int front;
    int back;
    int size;
    int capacity;
};
Deque *deque_construct(){
    Deque* deque = (Deque*)calloc(1, sizeof(Deque));
    deque->capacity = 4;
    deque->data = (int*)calloc(deque->capacity, sizeof(int));
    deque->front = 0;
    deque->back = 0;
    deque->size = 0;

    return deque;
}
void deque_push_back(Deque *f, int item){
    if(f->size == f->capacity){
        int new_capacity = f->capacity * 2;
        int* new_data = (int*)calloc(new_capacity, sizeof(int));
        for(int i = 0; i<f->size; i++){
            new_data[i] = f->data[(f->front + i)%f->capacity];
        }
        free(f->data);
        f->data = new_data;
        f->capacity = new_capacity;
        f->front = 0;
        f->back = f->size;    
    }
    f->data[f->back] = item;
    f->back = (f->back + 1) % f->capacity;
    f->size++;

}
void deque_push_front(Deque *f, int item){
    if(f->size == f->capacity){
        int new_capacity = f->capacity * 2;
        int* new_data = (int*)calloc(new_capacity, sizeof(int));
        for(int i = 0; i<f->size; i++){
            new_data[i] = f->data[(f->front + i)%f->capacity];
        }
        free(f->data);
        f->data = new_data;
        f->capacity = new_capacity;
        f->front = 0;
        f->back = f->size;    
    }
    f->front = (f->front -1 + f->capacity) % f->capacity;
    f->data[f->front] = item;
    f->size++;
}
int deque_pop_back(Deque *f){
    if(f->size == 0){
        return 0;
    }
    f->back = (f->back -1 + f->capacity) % f->capacity;
    int item = f->data[f->back];
    f->size--;

    return item;
}
int deque_pop_front(Deque *f){
    if(f->size == 0){
        return 0;
    }
    int item = f->data[f->front];
    f->front = (f->front + 1) % f->capacity;
    f->size--;

    return item;
}
void deque_destroy(Deque *f){
    free(f->data);
    free(f);
}