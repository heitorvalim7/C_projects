#ifndef _DATA_STRUCTURES_QUEUE_H_
#define _DATA_STRUCTURES_QUEUE_H_

typedef struct Stack Stack;

Stack *queue_construct();
void queue_destroy(Stack *q);
void queue_enqueue(Stack *q, void *val);
void queue_dequeue(Stack *q);
int queue_size(Stack *q);
#endif 