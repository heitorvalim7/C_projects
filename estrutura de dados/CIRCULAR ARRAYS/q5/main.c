#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

int main(){
    int n;

    scanf("%d", &n);
    Deque *d = deque_construct();
    for(int i = 0; i<n; i++){
        char op[20];
        scanf("%s", op);
        if(strcmp(op, "PUSH_BACK")==0){
            int item;
            scanf("%d", &item);
            deque_push_back(d, item);
        }
        else if(strcmp(op, "PUSH_FRONT")==0){
            int item;
            scanf("%d", &item);
            deque_push_front(d, item);
        }
        else if(strcmp(op, "POP_BACK")==0){
            int item = deque_pop_back(d);
            if(item != -100000){
                printf("%d\n", item);
            }
        }
        else if(strcmp(op, "POP_FRONT")==0){
            int item = deque_pop_front(d);
            if(item != -100000){
                printf("%d\n", item);
            }
        }
        else if(strcmp(op, "GET")==0){
            int idx;
            scanf("%d", &idx);
            int item = deque_get(d, idx);
            if(item != -100000){
                printf("%d\n", item);
            }
        }
    }
    deque_destroy(d);
    return 0;
}