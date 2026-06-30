#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int main(){
    int n;
    List *l = list_construct();
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        char order[100];
        scanf("%s", order);
        if(strcmp(order, "ENQUEUE")==0){
            char *string = (char*)calloc(100, sizeof(char));
            scanf("%s\n", string);
            list_push_back(l, string);
        } 
        else if(strcmp(order, "DEQUEUE")==0){
            char *string = (char*)list_pop_front(l);
            printf("%s\n", string);
            free(string);
        }
    }
    while(list_size(l) > 0){
        char *string = (char*)list_pop_front(l);
        free(string);
    }
    list_destroy(l);

    return 0;
}