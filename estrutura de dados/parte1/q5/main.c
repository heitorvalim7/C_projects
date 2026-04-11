#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



int main(){
    int n;
    int rodadas;
    int casaFinal = 0;

    scanf("%d", &n);
    scanf("%d", &rodadas);

    int f;
    for(int i = 0; i<rodadas; i++){
        scanf("%d", &f);
        casaFinal += f % n;
        if(casaFinal >= n){
            casaFinal = casaFinal % n;
        }
    }
    printf("%d\n", casaFinal);
}