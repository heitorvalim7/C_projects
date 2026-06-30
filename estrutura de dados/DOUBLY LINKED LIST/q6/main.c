#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n;
    Deque *f = deque_construct();
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char order[100];
        scanf("\n%s", order);
        if(strcmp(order, "PUSH_FRONT")==0){
            int i;
            scanf("%d", &i);
            deque_push_front(f, i);
        }
        else if(strcmp(order, "PUSH_BACK")==0){
            int i;
            scanf("%d", &i);
            deque_push_back(f, i);
        }
        else if(strcmp(order, "POP_BACK")==0){
            printf("%d\n", deque_pop_back(f));
        }
        else if(strcmp(order, "POP_FRONT")==0){
            printf("%d\n", deque_pop_front(f));
        }
    }
    deque_destroy(f);
    return 0;
}