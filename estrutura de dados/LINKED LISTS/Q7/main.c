
#include <stdio.h>

#include "forward_list.h"
void print(data_type a){
    int n = (int)a;
    printf("%d", n);
}

int main(){
    int n, valn;
    ForwardList *l1 = forward_list_construct();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &valn);
        forward_list_push_back(l1, valn);
    }
    printf("SIZE: %d\n", forward_list_size(l1));
    forward_list_print(l1, print);
    forward_list_destroy(l1);
}