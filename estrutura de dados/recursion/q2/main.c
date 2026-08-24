#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int function(int expoente, int base){
    if(expoente == 0){
        return 1;
    }
    expoente--;
    return base * function(expoente, base);
}

int main(){
    int expoente, base;

    scanf(" %d %d", &base, &expoente);
    function(expoente, base);
    printf("%d", function(expoente, base));
}