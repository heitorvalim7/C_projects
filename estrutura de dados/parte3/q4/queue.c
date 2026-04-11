#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue{
    Vector *v;
};

Queue *queue_construct(){
    Queue *q = (Queue*)calloc(1, sizeof(Queue));
    q->v = vector_construct();
    
    return q;
}
void queue_destroy(Queue *q){
    for(int i = 0; i<queue_size(q); i++){
        char *c = (char*)vector_get(q->v, i);
        free(c);
    }
    vector_destroy(q->v);
    free(q);
}
void queue_enqueue(Queue *q, void *val){
    vector_push_back(q->v, val);
}
void queue_dequeue(Queue *q){
    if(queue_size(q) == 0){
        exit(1);
    }
    char *c = (char*)vector_pop_front(q->v);
    printf("%s\n", c);
    free(c);
}
int queue_size(Queue *q){
    return vector_size(q->v);
}