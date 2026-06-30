#include "heap.h"
#include "deque.h"
#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    int n;
    scanf("%d", &n);
    Program **programs = (Program**)calloc(n, sizeof(Program*));
    for(int i = 0; i < n; i++){
        programs[i] = program_read();
    }
    Heap *SO = heap_construct(cmp_program);
    Heap *user = heap_construct(cmp_program);
    Deque *RT = deque_construct();

    int time = 0;
    int count = 0;
    while(count < n){
        for(int i = 0; i<n; i++){
            if(first_time(programs[i]) == time){
                if(strcmp(program_name(programs[i]), "SO") == 0){
                    heap_push(SO, programs[i]);
                }
                else if (strcmp(program_name(programs[i]), "USER") ==0){
                    heap_push(user, programs[i]);
                }
                else {
                    deque_push_back(RT, (int)programs[i]);
                }
            }
        }
    }
}