#include "forward_list.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_data(data_type data){
    int value = *(int*)data;
    printf("%d\n", value);
}

int main(){

    int num_instructions;
    scanf("%d", &num_instructions);

    ForwardList *list = forward_list_construct();

    for (int i = 0; i < num_instructions; i++){
        int value;
        scanf("%d", &value);
        int *data = (int*)calloc(1, sizeof(int));
        *data = value;
        forward_list_push_front(list, data);
    }

    forward_list_sort(list);
    forward_list_print(list, print_data);
    while(forward_list_size(list) > 0){
        data_type data = forward_list_pop_front(list);
        int *value = (int*)data;
        free(value);
    }
    forward_list_destroy(list);

    return 0;
}