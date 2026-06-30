#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Queue{
    void** data;
    int max_capacity;
    int size;
    int head;
    int rear;
};

Queue *queue_constructor(int max_capacity){
    Queue *queue = (Queue*)calloc(1, sizeof(Queue));
    queue->data = (void**)calloc(max_capacity, sizeof(void*));
    queue->max_capacity = max_capacity;
    queue->size = 0;
    queue->head = 0;
    queue->rear = 0;
    return queue;
}

// Add an element
void queue_add(Queue *queue, void *data){
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->max_capacity;
    queue->size++;
}

// Remove the oldest element in the queue
void* queue_remove(Queue *queue){
    void *data = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->max_capacity;
    queue->size--;
    return data;
}

// Return the number of elements in the queue
int queue_size(Queue *queue){
    return queue->size;
}
// Return 1 if the queue is full and 0, otherwise
int queue_is_full(Queue *queue){
    return queue->size == queue->max_capacity;
}

// Return 1 if the queue is empty and 0, otherwise
int queue_is_empty(Queue *queue){
    return queue->size == 0;
}

// Free the data structure.
// IMPORTANT: the user of the lib is responsible for removing and freeing elements
// remaining in the queue. In the queue is not empty when the functions is called,
// the function will not release them.
void queue_destroy(Queue *queue){
    free(queue->data);
    free(queue);
}