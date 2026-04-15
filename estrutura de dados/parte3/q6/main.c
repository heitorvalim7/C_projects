#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct{
    char nome[32];
    Vector *materias;
    float percentualRepro;
} Professor;

typedef struct{
    char nome[32];
    int alunosAp;
    int alunoMat;
    float percentualRepro;
} Disciplinas;

int main (){
    int n;
    scanf("%d", &n);
    Professor **p = (Professor**)calloc(n, sizeof(Professor*));
    
    for(int i = 0; i<n; i++){
        p[i] = (Professor*)calloc(1, sizeof(Professor));
        p[i]->materias = vector_construct();
        p[i]->percentualRepro = 0;
        scanf("\n%s", p[i]->nome);
        int m;
        scanf("%d", &m);
        for(int j = 0; j<m; j++){
            Disciplinas *d = (Disciplinas*)calloc(1, sizeof(Disciplinas));
            scanf("\n%s %d %d", d->nome, &d->alunoMat, &d->alunosAp);
            d->percentualRepro = 100.0 * (d->alunoMat - d->alunosAp)/ d->alunoMat;
            vector_push_back(p[i]->materias, d);
            p[i]->percentualRepro += d->percentualRepro;
        }
        int s = vector_size(p[i]->materias);
        p[i]->percentualRepro /= s;
    }

    int mediaP = 0;
    for(int i = 0; i<n; i++){
        mediaP += p[i]->percentualRepro;
    }
    mediaP /= n;
    for(int i = 0; i<n; i++){
        if(p[i]->percentualRepro > mediaP){
            printf("%s\n", p[i]->nome);
        }
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<vector_size(p[i]->materias); j++){
            Disciplinas *d = (Disciplinas*)vector_get(p[i]->materias, j);
            free(d);
        }
        vector_destroy(p[i]->materias);
        free(p[i]);
    }
    free(p);

}