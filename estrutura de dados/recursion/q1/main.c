#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void function(int init, int end, int update){

    if(init == end){
        return;
    }
    
    printf("%d\n", init);
    
    init += update;

    return function(init, end, update);
}

int main(){
    int init, end, update;

    scanf(" %d %d %d", &init, &end, &update);
    function(init, end, update);
}