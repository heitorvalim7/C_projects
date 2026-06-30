#ifndef _PROGRAM_H_
#define _PROGRAM_H_
#include "deque.h"
#include "heap.h"

typedef struct Program Program;
Program *program_construct();
Program *program_read();
int first_time(Program *p);
int cmp_program(void *a, void *b);
char *program_name(Program *p);
#endif