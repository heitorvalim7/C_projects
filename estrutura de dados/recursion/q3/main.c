
#include <stdio.h>

#include "forward_list.h"

void recursive_print(void *no){
    Node *n = (Node*)no;
    if(n != NULL){
        printf("%d", (int)n->value);
        n = n->next;
    }

    if(n != NULL){
        printf(", ");
        return recursive_print(n);
    }
}


int main()
{
    int n, val;

    ForwardList *l = forward_list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        forward_list_push_front(l, val);
    }

    // test the size and print functions
    printf("Size: %d\n", forward_list_size(l));
    forward_list_print(l, recursive_print);
    printf("\n");

    // test the destroy function
    forward_list_destroy(l);

    return 0;
}