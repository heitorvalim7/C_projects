#include "hash.h"
#include "vector.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int hash_fn(HashTable *h, void *string){
    int hash = 0;
    int b = 127;
    char *str = string;
    for(int i = 0; i<strlen(string); i++){
        hash = (hash * b + str[i]) % hash_table_size(h);
    }

    return hash;
}

int cmp_hash(void *a, void* b){
    char *s1 = (char*)a;
    char *s2 = (char*)b;

    return strcmp(s1, s2);
}

int main(){
    int base, table_size;
    
    scanf("%d %d", &table_size, &base);

    HashTable *h = hash_table_construct(table_size, hash_fn, cmp_hash);
    for(int i = 0; i<table_size; i++){
        char order[5];
        scanf(" %s", order);
        if(strcmp(order, "ADD")==0){
            char *name = (char*)calloc(10, sizeof(char));
            int qtd;
            scanf(" %[^ ] %d", name, &qtd);
            int torem = *(int *)hash_table_set(h, name, qtd);
        }
        else if(strcmp(order, "USE")==0){
            char *name = (char*)calloc(10, sizeof(char));
            int qtd;
            scanf(" %[^ ] %d", name, &qtd);
            int torem = *(int *)hash_table_get(h, name, qtd);
        }
        else if(strcmp(order, "SCRAP")==0){
            char *name = (char*)calloc(10, sizeof(char));
            scanf(" %s", &name);
            
        }

    }
}