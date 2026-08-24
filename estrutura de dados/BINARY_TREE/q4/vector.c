#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector *vector_construct(){

    Vector *v = (Vector*)calloc(1, sizeof(Vector));
    v->size = 0;
    v->allocated = 2;
    v->data = (data_type *)calloc(2, sizeof(data_type));
    return  v;
}
void vector_destroy(Vector *v){
    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, data_type val){
    if(v->allocated == v->size){
        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if(i < v->size){
        return v->data[i];
    }

    printf("error");
    exit(1);
}
void vector_set(Vector *v, int i, data_type val){
    if(i < v->size){
        v->data[i] = val;
    }
}
int vector_size(Vector *v){
    return v->size;
}


int vector_find(Vector *v, data_type val){
    for(int i = 0; i<v->size; i++){
        if(v->data[i] == val){
            return i;
        }
    }

    return -1;
}

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v){
    data_type maior = v->data[0];
    for(int i = 0; i<v->size; i++){
        if(v->data[i] > maior){
            maior = v->data[i];
        }
    }
    return maior;
}

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v){
    data_type menor = v->data[0];
    for(int i = 0; i<v->size; i++){
        if(v->data[i] < menor){
            menor = v->data[i];
        }
    }
    return menor;
}

// Retorna o ÃƒÂ­ndice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v){
    data_type maior = v->data[0];
    int idx;
    for(int i = 0; i<v->size; i++){
        if(v->data[i] >= maior){
            maior = v->data[i];
            idx = i;
        }
    }
    return idx;
}

// Retorna o ÃƒÂ­ndice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v){
    data_type menor = v->data[0];
    int idx;
    for(int i = 0; i<v->size; i++){
        if(v->data[i] <= menor){
            menor = v->data[i];
            idx = i;
        }
    }
    return idx;
}
void vector_swap(Vector *v, int i, int j){
    data_type data;
    data = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = data;
}
data_type vector_remove(Vector *v, int i){
    data_type removed;
    removed = v->data[i];
    for(int j = i; j<v->size; j++){
        v->data[j] = v->data[j+1];
    }
    v->size --;
    return removed;
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val){
    if(i > v->size){
        exit(1);
    }
    if(v->allocated == v->size){ 
        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }
    for(int j = v->size; j>i; j--){
        v->data[j]= v->data[j-1];
    }
    v->data[i]= val;
    v->size++;
}

data_type vector_pop_front(Vector *v){
    data_type removed;
    removed = v->data[0];
    for(int i = 0; i<v->size; i++){
        v->data[i] = v->data[i+1];
    }
    v->size --;
    return removed;
}

data_type vector_pop_back(Vector *v){
    data_type removed;
    removed = v->data[v->size-1];
    v->size --;
    return removed;
}

void vector_reverse(Vector *v){
    for(int i = 0; i<v->size/2; i++){
        vector_swap(v, i, v->size-1-i);
    }
}

void vector_sort(Vector *v){
    for(int i = 0; i<v->size-1; i++){
        int flag = 0;
        for(int j = 0; j<v->size-1-i; j++){
            if(v->data[j] > v->data[j+1]){
                vector_swap(v, j, j+1);
                flag = 1;
            }
        }
        if(flag == 0){
            break;
        }
    }
}
int vector_binary_search(Vector *v, data_type val){
    int left = 0, right = v->size-1;
    while(left <= right){
        int mid = (left + right)/2;
        if(v->data[mid] == val){
            return mid;
        }
        else if(v->data[mid] < val){
            left = mid + 1;

        } else {
            right = mid - 1;
        }
    }
    return -1;
}
