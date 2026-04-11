#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);
    filme **listafilmes = (filme**)calloc(n, sizeof(filme*));
    float mediaTotal = 0;
    for(int i = 0; i<n; i++){
        listafilmes[i] = leFilme();
        mediaTotal += retornaMedia(listafilmes[i]);
    }

    mediaTotal = mediaTotal / n;

    for(int i = 0; i<n; i++){
        if(retornaMedia(listafilmes[i])>mediaTotal){
            imprimeFilme(listafilmes[i]);
        }
    }
    desaloca(listafilmes, n);
}