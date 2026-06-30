
#include <stdio.h>

#include "forward_list.h"
void print(data_type a){
    int n = (int)a;
    printf("%d\n", n);
}

int main(){
    int n, valn;
    ForwardList *l1 = forward_list_construct();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &valn);
        forward_list_push_front(l1, valn);
    }
    ListIterator *it = list_iterator_construct(l1);
    while(!list_iterator_is_over(it)){
        data_type *value = list_iterator_next(it);
        *value = *value * 2;
    }
    forward_list_print(l1, print);
    forward_list_destroy(l1);
    list_iterator_destroy(it);
}