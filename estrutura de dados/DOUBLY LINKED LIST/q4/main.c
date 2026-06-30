#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    int n;
    List *l = list_construct();

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        char order[5];
        scanf("\n%s", order);
        if(strcmp(order, "PUSH") == 0){
            char *data = (char*)calloc(100, sizeof(char)); 
            scanf("%s", data);
            list_push_front(l, data);
        }
        else if(strcmp(order, "POP") == 0){
            if(list_size(l) == 0){
                printf("EMPTY\n");

            }
            else{
                char *data = (char*)list_pop_front(l);

                printf("%s\n", data);
                free(data);
            }
        }
    }
    while(list_size(l) > 0){
        char *data = (char*)list_pop_front(l);
        free(data);
    }
    list_clear(l); 
    list_destroy(l);
    return 0;
}