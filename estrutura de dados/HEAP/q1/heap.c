#include "heap.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Heap
{
    Vector *data;
    cmp_fn cmp;
};

// Cria um heap vazio
Heap *heap_construct(cmp_fn cmp){
    Heap *h = (Heap*)calloc(1, sizeof(Heap));
    h->data = vector_construct();
    h->cmp = cmp;

    return h;
}

// Libera memória do heap
void heap_destroy(Heap *h, void(*free_item)(void *)){
    for(int i = 0; i<vector_size(h->data); i++){
        free_item(vector_get(h->data, i));
    }

    free(h->data);
    free(h);
}

// Insere um elemento no heap
void heap_push(Heap *h, data_type value){
    vector_push_back(h->data, value);
    int i = vector_size(h->data) - 1;
    while(i != 0){
        int idxpai = (i-1)/2;
        if(h->cmp(vector_get(h->data, idxpai), vector_get(h->data, i)) < 0){
            vector_swap(h->data, i, idxpai);
            i = idxpai;
        }
        else break;

    }
    
}

// Retorna o número de elementos
int heap_size(Heap *h){
    return vector_size(h->data);
}

// Verifica se está vazio
int heap_empty(Heap *h){
    if(vector_size(h->data)==0){
        return 1;
    }
    return 0;
}

void heap_print(Heap *h, void(print_item)(void *)){
    for(int i = 0; i<vector_size(h->data); i++){
        print_item(vector_get(h->data, i));
    }
}


// implementações das funções
