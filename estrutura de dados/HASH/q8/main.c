#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hash_str(HashTable *h, void *str){
    char *string = (char*)str;
    long hash_val = 0;
    int base = 127;
    for(size_t i = 0; i<strlen(string); i++){
        hash_val = (base * hash_val + string[i]) % hash_table_size(h);
    }
    return hash_val;
}

int str_cmp(void* a, void* b){
    char *str1 = (char*)a;
    char *str2 = (char*)b;

    return strcmp(str1, str2);
}

int cmp_hash(const void *a, const void *b){
    HashTableItem *h1 = (HashTableItem*)a;
    HashTableItem *h2 = (HashTableItem*)b;
    
    return str_cmp(h1->key, h2->key);
}


int main(){
    int n;
    scanf("%d", &n);
    HashTable *h = hash_table_construct(n, hash_str, str_cmp);
    for(int i = 0; i<n; i++){
        char *nome = (char*)calloc(100, sizeof(char));
        scanf(" %s", nome);
        int *freq = (int*)hash_table_get(h, nome);
        
        if(freq == NULL){
            freq = (int*)calloc(1, sizeof(int));
            *freq = 1;
            int *value = (int*)hash_table_set(h, nome, freq);
            if(value != NULL){
                free(value);
            }
        } else{
            *freq += 1;
            free(nome);
        }

      
    }
    Vector *v = hash_to_vector(h);
    vector_sort(v, cmp_hash);
    int size = vector_size(v);
    for(int i = 0; i<size; i++){
        HashTableItem *popped = (HashTableItem*)vector_get(v, i);
        printf("%s %d\n", (char*)popped->key, *(int*)popped->val);
    }
    vector_destroy(v);
    hash_table_destroy(h);

    return 0;
}