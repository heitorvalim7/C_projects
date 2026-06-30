#include "hash.h"
#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *hash_tbl = (HashTable*)calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = (ForwardList**)calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val){
    
    int hash = h->hash_fn(h, key);

    if (h->buckets[hash] == NULL) {
        h->buckets[hash] = forward_list_construct();
    }

    Node *n = h->buckets[hash]->head;

    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)==0){
            void* ret = item->val;
            item->val = val;
            return ret;
        }
        n = n->next;
    }
    HashTableItem *new_item = (HashTableItem*)calloc(1, sizeof(HashTableItem));
    new_item->key = key;
    new_item->val = val;
    h->n_elements++;
    forward_list_push_front(h->buckets[hash], new_item);

    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);
    Node *n = h->buckets[hash]->head;
    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)==0){
            void* ret = item->val;
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
int hash_table_num_elems(HashTable *h);

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h){

    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = (HashTableItem*)n->value;
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
HashTableIterator *hash_table_iterator(HashTable *h);

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it);

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it);

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it);
