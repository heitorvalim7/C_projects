
#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_construct();
void heap_push(Heap *h, void* item);
void *heap_pop(Heap *h);
void heap_update(Heap *h);
void heap_print(Heap *h);
void heap_destroy(Heap *h);

#endif