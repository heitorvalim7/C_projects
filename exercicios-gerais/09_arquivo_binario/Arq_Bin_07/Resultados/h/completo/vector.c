#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Vector{
    DataType *vector;
    int numElem;
};

/**
 * @brief Cria um vetor vazio
 * 
 * @return A estrutura Vector inicializada. Caso não seja possível alocar memória, o programa é encerrado.
*/
Vector *VectorConstruct(){
    Vector *v = (Vector*)calloc(1, sizeof(Vector));
    v->vector=NULL;
    v->numElem=0;

    return v;
}

/**
 * @brief Adiciona um elemento no final do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param val Valor a ser adicionado
*/
void VectorPushBack(Vector *v, DataType val){
    if(!v){
        return;
    }
    v->vector = (DataType*)realloc(v->vector, (v->numElem + 1) * sizeof(DataType));
    v->vector[v->numElem] = val;
    v->numElem++;
}

/**
 * @brief Remove o i-ésimo elemento do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param i Índice do elemento
*/
void VectorRemove(Vector *v, int i) {
    if (!v || i < 0 || i >= v->numElem) {
        return;
    }

    free(v->vector[i]);


    for (int j = i; j < v->numElem - 1; j++) {
        v->vector[j] = v->vector[j + 1];
    }

    v->numElem--;

    if (v->numElem > 0) {
        DataType *temp = (DataType*)realloc(v->vector, v->numElem * sizeof(DataType));
        if (temp) {
            v->vector = temp;
        }
    } else {
        free(v->vector);
        v->vector = NULL;
    }
}

/**
 * @brief Retorna o i-ésimo elemento do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param i Índice do elemento
 * @return DataType Elemento do vetor
*/
DataType VectorGet(Vector *v, int i){
    if(i<0 || i>=v->numElem){
        return NULL;
    }

    return v->vector[i];
}

/**
 * @brief Retorna o tamanho do vetor
 * 
 * @param v Ponteiro para o vetor
 * @return int Tamanho do vetor
*/
int VectorSize(Vector *v){
    return v->numElem;
}


/**
 * @brief Troca os elementos i e j do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param i Índice do primeiro elemento
 * @param j Índice do segundo elemento
*/
void VectorSwap(Vector *v, int i, int j){
    DataType temp;
    temp = VectorGet(v, i);
    v->vector[i] = v->vector[j];
    v->vector[j] = temp;
}

/**
 * @brief Libera a memória alocada para o vetor
 * 
 * @param v Ponteiro para o vetor
 * @param destroy Função que libera a memória alocada para cada elemento do vetor
*/
void VectorDestroy(Vector *v, void (*destroy)(DataType)){
    for(int i = 0; i<v->numElem; i++){
        destroy(v->vector[i]);
    }
    free(v->vector);
    free(v);
}