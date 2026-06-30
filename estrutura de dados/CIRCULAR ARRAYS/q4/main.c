#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    Deque *d = deque_construct();
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char op[20];
        scanf("%s", op);
        
        if(strcmp(op, "PUSH_BACK") == 0){
            int item;
            scanf("%d", &item);
            deque_push_back(d, item);
        }
        else if(strcmp(op, "PUSH_FRONT") == 0){
            int item;
            scanf("%d", &item);
            deque_push_front(d, item);
        }
        else if(strcmp(op, "POP_BACK")== 0){
            int item = deque_pop_back(d);
            if(item != 0){
                printf("%d\n", item);
            }
        }
        else if(strcmp(op, "POP_FRONT")== 0){
            int item = deque_pop_front(d);
            if(item != 0){
                printf("%d\n", item);
            }
        }
    }
    deque_destroy(d);
    return 0;
}