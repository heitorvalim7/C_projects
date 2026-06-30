#include "hash.h"
#include "forward_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct HashTable{
    ForwardList **buckets;
    int n_elements;
    int table_size;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)calloc(1, sizeof(HashTable));
    h->table_size = table_size;
    h->buckets = (ForwardList**)calloc(table_size, sizeof(ForwardList*));
    h->n_elements = 0;
    h->cmp_fn = cmp_fn;
    h->hash_fn = hash_fn;

    return h;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val){
    int hash = h->hash_fn;
    if(h->buckets[hash]==NULL){
        h->buckets[hash] = forward_list_construct();
    }
    Node *n = h->buckets[hash]->head;
    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)){
            void *torem = item->val;
            int qtd = *(int *)item->val + *(int*)val;
            item->val = qtd;
            return torem;
        }
        n = n->next;
    }
    HashTableItem *item = (HashTableItem*)calloc(1, sizeof(HashTableItem));
    item->key = key;
    item->val = val;
    h->n_elements++;
    forward_list_push_front(h->buckets[hash], item);

    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key, void *val){
    int hash = h->hash_fn;
    if(h->buckets[hash]==NULL){
        printf("peça nao encontrada\n");
        return NULL;
    }
    Node *n = h->buckets[hash]->head;
    while(n != NULL){
        HashTableItem *item = (HashTableItem*)n->value;
        if(h->cmp_fn(item->key, key)){
            void *torem = item->val;
            int qtd = *(int *)item->val - *(int*)val;
            item->val = qtd;
            return torem;
        }
        n = n->next;
    }
    printf("peça nao encontrada\n");

}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);
    if(h->buckets[hash] == NULL){
        return NULL;
    }

    Node *n = h->buckets[hash]->head;
    int index = 0;
    while(n != NULL){
        HashTableItem* it = (HashTableItem*)n->value;
        if(h->cmp_fn(it->key, key)==0){
            
            int ret = (int)it->val;
            char *rem = (char*)it->val;
            free(rem);
            free(it);
            forward_list_pop_index(h->buckets[hash], index);
            h->n_elements--;
            return ret;
        }
        n = n->next;
        index++;
    }
    return NULL;
}

// numero de buckets
int hash_table_size(HashTable *h){
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h);

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h);

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h);

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it);

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it);

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it);

Vector *hash_to_vector(HashTable *h);