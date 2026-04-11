#ifndef _DATA_STRUCTURES_QUEUE_H_
#define _DATA_STRUCTURES_QUEUE_H_

typedef struct Queue Queue;

Queue *queue_construct();
void queue_destroy(Queue *q);
void queue_enqueue(Queue *q, void *val);
void queue_dequeue(Queue *q);
int queue_size(Queue *q);
#endif 