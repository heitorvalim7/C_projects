#include "priority_queue_vector.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct PriorityQueue{
    Vector *data;
    int (*cmp_fn)(const void*, const void*);
};

PriorityQueue *pq_constructor(int cmp_fn(const void *, const void *)){
    PriorityQueue *pq = (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
    pq->data = vector_construct();
    pq->cmp_fn = cmp_fn;
    return pq;
}
void pq_push(PriorityQueue *pq, void *data){
    vector_push_back(pq->data, data);
    int i = vector_size(pq->data)-1;
    while(i != 0){
        int idxpai = (i-1)/2;
        if(pq->cmp_fn(vector_get(pq->data, idxpai), vector_get(pq->data, i)) < 0){
            vector_swap(pq->data, i, idxpai);
            i = idxpai;
        }
        else break;
    }
}
void *pq_pop(PriorityQueue *pq){
    void *removed = vector_get(pq->data, 0);
    vector_swap(pq->data, 0, vector_size(pq->data)-1);
    vector_pop_back(pq->data);
    int i = 0;
    while(1){
        int idxfilho1 = 2*i + 1;
        int idxfilho2 = 2*i + 2;
        int idxmaior = i;
        if(idxfilho1 < vector_size(pq->data) && pq->cmp_fn(vector_get(pq->data, idxfilho1), vector_get(pq->data, idxmaior)) > 0){
            idxmaior = idxfilho1;
        }
        if(idxfilho2 < vector_size(pq->data) && pq->cmp_fn(vector_get(pq->data, idxfilho2), vector_get(pq->data, idxmaior)) > 0){
            idxmaior = idxfilho2;
        }    
        if(idxmaior != i){
            vector_swap(pq->data, i, idxmaior);
            i = idxmaior;
        }
        else break;
    }
    return removed;
}
int pq_size(PriorityQueue *pq){
    return vector_size(pq->data);
}
void pq_destroy(PriorityQueue *pq){
    vector_destroy(pq->data);
    free(pq);
}