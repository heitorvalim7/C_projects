#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long hash(int seed, char *str, int update, int table_size){
    int len = strlen(str);
    long long hash_val = seed;
    for(int i = 0; i<len; i++){
        hash_val = (hash_val * update + str[i]) % table_size;
    }
    return hash_val;
}

int main(){
    int seed, update, table_size, n_strings;
    scanf("%d %d %d", &seed, &update, &table_size);
    scanf("%d", &n_strings);
    for(int i = 0; i<n_strings; i++){
        char nome[100];
        scanf("\n%s", nome);
        printf("%lld\n", hash(seed, nome, update, table_size));
    }
    return 0;
}