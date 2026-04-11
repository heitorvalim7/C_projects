#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "vector.h"

int main(){
    int n;
    scanf("%d", &n);
    Queue *q = queue_construct();

    for(int i = 0; i<n; i++){
        char c[100];
        scanf("%s", c);

        if(c[0] ==  'E'){
            char *string = (char*)malloc(100 * sizeof(char));
            scanf("%s", string);
            queue_enqueue(q,string);
        }
        else if(c[0] == 'D'){
            queue_dequeue(q);
        }
    }
    queue_destroy(q);
}