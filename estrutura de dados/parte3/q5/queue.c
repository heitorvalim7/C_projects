#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Stack{
    Vector *v;
};

Stack *queue_construct(){
    Stack *q = (Stack*)calloc(1, sizeof(Stack));
    q->v = vector_construct();
    
    return q;
}
void queue_destroy(Stack *q){
    for(int i = 0; i<queue_size(q); i++){
        char *c = (char*)vector_get(q->v, i);
        free(c);
    }
    vector_destroy(q->v);
    free(q);
}
void queue_enqueue(Stack *q, void *val){
    vector_push_back(q->v, val);
}
void queue_dequeue(Stack *q){
    if(queue_size(q) == 0){
        exit(1);
    }
    char *c = (char*)vector_pop_back(q->v);
    printf("%s\n", c);
    free(c);
}
int queue_size(Stack *q){
    return vector_size(q->v);
}