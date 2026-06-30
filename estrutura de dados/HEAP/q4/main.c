#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue_vector.h"
#include "vector.h"

typedef struct{
    char nome[32];
    int prioridade;
}Processo;

Processo* le_processo(){
    Processo *p = (Processo*)calloc(1, sizeof(Processo));
    scanf("\n%s %d", p->nome, &p->prioridade);

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

    printf("\n%s %d", p->nome, p->prioridade);
}
void destroy(void *processo){
    Processo *p = (Processo*) processo;
    free(p);
}


int main(){
    int n;
    PriorityQueue *pq = pq_constructor(comparaFunc);
    scanf("%d", &n);
    char order[10];

    for(int i = 0; i<n; i++){ 
        scanf("\n%s", order);
        if(strcmp(order, "ADICIONAR") == 0){
            Processo *p = le_processo();
            pq_push(pq, p);
        }
        else if(strcmp(order, "CHAMAR") == 0){
            Processo *p = (Processo*) pq_pop(pq);
            imprime(p);
            destroy(p);
        }
    }

    if(pq_size(pq) > 0){
        while(pq_size(pq) > 0){
            Processo *p = (Processo*) pq_pop(pq);
            imprime(p);
            destroy(p);
        }
    }
    pq_destroy(pq);
}