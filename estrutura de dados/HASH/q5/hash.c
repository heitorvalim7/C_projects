#include "hash.h"
#include "forward_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator{
    HashTable *h;
    int current_bucket;
    Node *current_node;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)calloc(1, sizeof(HashTable));
    h->table_size = table_size;
    h->buckets = (ForwardList**)calloc(h->table_size, sizeof(ForwardList*));
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
        h->buckets[hash] = forward_list_construct();
    }
    
    Node *n = h->buckets[hash]->head;

    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)==0){
            void *ret = item ->val;
            item->val = val;
            return ret;
        }
        n = n->next;
    }
    HashTableItem *new_item = (HashTableItem*)calloc(1, sizeof(HashTableItem));
    new_item->val = val;
    new_item->key = key;
    forward_list_push_front(h->buckets[hash], new_item);
    h->n_elements++;
    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);

    if(h->buckets[hash] == NULL){
        return NULL;
    }

    Node *n = h->buckets[hash]->head;

    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)==0){
            void *ret = item ->val;
            return ret;
        }
        n = n->next;
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
int hash_table_num_elems(HashTable *h){
    return h->n_elements;
}

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h){
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = (HashTableItem*) n->value;
                free(pair->key);
                free(pair->val);
                free(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
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
    it->current_node = NULL;

    for(int i = 0; i < h->table_size; i++){
        if(h->buckets[i] != NULL && h->buckets[i]->size > 0){
            it->current_bucket = i;
            it->current_node = h->buckets[i]->head;
            break;
        }
    }

    return it;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it){
    if(it->current_node == NULL){
        return 1;
    }
    return 0;
}

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    if(hash_table_iterator_is_over(it)){
        return NULL;
    }
    HashTableItem *item = (HashTableItem*)it->current_node->value;
    it->current_node = it->current_node->next;
    
    if(it->current_node == NULL){
        for(int i = it->current_bucket + 1; i < it->h->table_size; i++){
            if(it->h->buckets[i] != NULL && it->h->buckets[i]->size > 0){
                it->current_bucket = i;
                it->current_node = it->h->buckets[i]->head;
                break;
            } 
        }
    }
    return item;

}

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}
