#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include "filme.h"  

struct filme{
    char nome[32];
    float *notas;
    int n;
    float notaMedia;
};

filme* criaFilme(char *nome, float *notas, int n){
    filme *f = (filme*)calloc(1, sizeof(filme));
    strcpy(f->nome, nome);
    f->n = n;
    f->notas = notas;
    f->notaMedia = calculaMedia(notas, n);
    return f;
}

filme* leFilme(){
    char nome[32];
    int n;
    scanf("%s\n", nome);
    scanf("%d", &n);
    float *notas = (float *)calloc(n, sizeof(float));
    for(int i = 0; i<n; i++){
        scanf("%f", &notas[i]);
    }  
    filme *f = criaFilme(nome, notas, n);
    return f;
}

float calculaMedia(float *notas, int n){
    float media = 0;
    for(int i = 0; i<n; i++){
        media += notas[i];
    }
    return media/n;
}

float retornaMedia(filme *f){
    return f->notaMedia;
}

void imprimeFilme(filme *f){
    printf("%s\n", f->nome);
}
void desaloca(filme **f, int n){
    for(int i = 0; i<n; i++){
        free(f[i]->notas);
        free(f[i]);
    }
    free(f);
}