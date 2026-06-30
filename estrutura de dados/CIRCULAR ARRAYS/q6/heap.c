#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Heap{
    void **arr;
    int size;
    int capacity;
    int (*cmp)(void*, void*);
};

Heap *heap_construct(int (*cmp)(void*, void*)){
    Heap *h = (Heap*)calloc(1, sizeof(Heap));
    h->arr = (void**)calloc(10, sizeof(void*));
    h->size = 0;
    h->capacity = 10;
    h->cmp = cmp;

    return h;
}
void heap_push(Heap *h, void* item){
    if(h->size == h->capacity){
       h->arr = (void**)realloc(h->arr, (h->capacity * 2) * sizeof(void*));
       h->capacity *= 2;
    }
    h->arr[h->size] = item;
    h->size++;
    int i = h->size - 1;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(h->cmp(h->arr[i], h->arr[parent]) < 0){
            void *temp = h->arr[i];
            h->arr[i] = h->arr[parent];
            h->arr[parent] = temp;
            i = parent;

        }
        else break;
    }
    

}
void* heap_pop(Heap *h){
    if(h->size == 0) return NULL;
    void *first = h->arr[0];
    h->arr[0] = h->arr[h->size -1];
    h->size--;
    int i = 0;
    while(1){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if(left < h->size && h->cmp(h->arr[left], h->arr[smallest]) < 0){
            smallest = left;
        }
        if(right < h->size && h->cmp(h->arr[right], h->arr[smallest]) < 0){
            smallest = right;
        }
        if(smallest != i){
            void *temp = h->arr[i];
            h->arr[i] = h->arr[smallest];
            h->arr[smallest] = temp;
            i = smallest;

        }
        else break;
    }
    
    return first;
}

void heap_destroy(Heap *h){
    free(h->arr);
    free(h);
}