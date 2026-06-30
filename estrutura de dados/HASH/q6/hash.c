#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

struct HashTable{
    Vector **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator{
    HashTable *h;
    int current_bucket;
    int current_item;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)calloc(1, sizeof(HashTable));
    h->table_size = table_size;
    h->buckets = (Vector**)calloc(h->table_size, sizeof(Vector*));
    h->cmp_fn = cmp_fn;
    h->hash_fn = hash_fn;
    h->n_elements = 0;

    return h;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val){
    int hash = h->hash_fn(h, key);
    if(h->buckets[hash] == NULL){
        h->buckets[hash] = vector_construct();
    }
    Vector *v = h->buckets[hash];
    int current_size = vector_size(v);
    for(int i = 0; i<current_size; i++){
        HashTableItem *item = (HashTableItem*)vector_get(v, i);
        if(h->cmp_fn(item->key, key)==0){
            void *ret = item->val;
            item->val = val;

            return ret;
        }
    }
    HashTableItem *new_item = (HashTableItem*)calloc(1, sizeof(HashTableItem));
    new_item->key = key;
    new_item->val = val;
    vector_insert(h->buckets[hash], 0, new_item);
    h->n_elements++;

    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);
    if(h->buckets[hash] == NULL){
        h->buckets[hash] = vector_construct();
    }
    Vector *v = h->buckets[hash];

    int current_size = vector_size(v);

    for(int i = 0; i<current_size; i++){
        HashTableItem *item = (HashTableItem*)vector_get(v, i);
        if(h->cmp_fn(item->key, key)==0){
            void *ret = item->val;

            return ret;
        }
    }

    return NULL;
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key);

// numero de buckets
int hash_table_size(HashTable *h){
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h);

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h){
    if(h == NULL) return;

    for(int i = 0; i<hash_table_size(h); i++){
        if(h->buckets[i] != NULL){
            int current_size = vector_size(h->buckets[i]);
            for(int j = 0; j<current_size; j++){
                HashTableItem *tofree = (HashTableItem*)vector_get(h->buckets[i], j);
                free(tofree);
            }
            vector_destroy(h->buckets[i]);
        }
        
    }
    free(h->buckets);
    free(h);
}

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h){
    HashTableIterator *it = (HashTableIterator*)calloc(1, sizeof(HashTableIterator));
    it->h = h;
    it->current_bucket = 0;
    it->current_item = 0;

    for(int i = 0; i<hash_table_size(h); i++){
        if(h->buckets[i] != NULL && vector_size(h->buckets[i]) > 0){
            it->current_bucket = i;
            break;
        }
    }
    return it;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it){
    if(it == NULL || it->current_bucket >= it->h->table_size){
        return 1;
    }
    return 0;
}

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    if(hash_table_iterator_is_over(it)){
        return NULL;
    }
    Vector *v = it->h->buckets[it->current_bucket];
    HashTableItem *current_item = (HashTableItem*) vector_get(v, it->current_item);
    it->current_item++;
    if(it->current_item >= vector_size(v)){
        it->current_item = 0;
        it->current_bucket++;
        while(it->current_bucket < it->h->table_size){
            Vector *next_v = it->h->buckets[it->current_bucket];
            if(next_v != NULL && vector_size(next_v) > 0){
                break;
            }
            it->current_bucket++;
        }
    }
    return current_item;
}
// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it){
    if(it != NULL){
        free(it);
    }
}

Vector *hash_to_vector(HashTable *h){
    if(h == NULL){
        return NULL;
    }
    
    Vector *v = vector_construct();
    HashTableIterator * it = hash_table_iterator(h);

    while(!hash_table_iterator_is_over(it)){
        HashTableItem *item = hash_table_iterator_next(it);
        vector_push_back(v, item);
    }
    hash_table_iterator_destroy(it);
    return v;
}
