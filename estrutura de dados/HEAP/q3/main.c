#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue_vector.h"
#include "vector.h"

typedef struct{
    char nome[32];
    char categoria[32];
    int identificador;
    int prioridade;
}Processo;

Processo* le_processo(){
    Processo *p = (Processo*)calloc(1, sizeof(Processo));
    scanf("\n%s %s %d %d", p->nome, p->categoria, &p->identificador, &p->prioridade);

    return p;

}
int comparaFunc(const void *P1, const void *P2){
    Processo* p1 = (Processo*)P1;
    Processo* p2 = (Processo*)P2;


    if((p1->prioridade - p2->prioridade)<0 ){
        return -1;
    }
    return 1;
}
void imprime(void *processo){
    Processo *p = (Processo*) processo;

    printf("\n%s %s %d %d", p->nome, p->categoria, p->identificador, p->prioridade);
}
void destroy(void *processo){
    Processo *p = (Processo*) processo;
    free(p);
}


int main(){
    int n;
    PriorityQueue *pq = pq_constructor(comparaFunc);
    scanf("%d", &n);

    for(int i = 0; i<n; i++){ 
        Processo *p = le_processo();
        pq_push(pq, p);
    }
    
    for(int i = 0; i<n; i++){
        Processo *p = (Processo*) pq_pop(pq);
        imprime(p);
        destroy(p);
    }
    pq_destroy(pq);
}