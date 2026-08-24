#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *key;
    void *value;
    struct Node *l;
    struct Node *r;
}Node;

struct BinaryTree{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn keydestroy_fn;
    ValDestroyFn valdestroy_fn;
};
KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *k = (KeyValPair*)calloc(1, sizeof(KeyValPair));
    k->key = key;
    k->value = val;
    return k;
}
void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp->key);
    free(kvp->value);
    free(kvp);
}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *b = (BinaryTree*)calloc(1, sizeof(BinaryTree));
    b->cmp_fn = cmp_fn;
    b->keydestroy_fn = key_destroy_fn;
    b->valdestroy_fn = val_destroy_fn;
    b->root = NULL;

    return b;
}

Node *node_construct(void *key, void *val){
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->key = key;
    n->value = val;
    n->l = NULL;
    n->r = NULL;

    return n;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    if(bt->root == NULL){
        bt->root = node_construct(key, value);
        return;
    }
    Node *n = bt->root;
    while(n != NULL){
        if(bt->cmp_fn(key, n->key)<0){
            if(n->l != NULL){
                n = n->l;
            }
            else{
                n->l = node_construct(key, value);
                return;
            }
        }
        else if(bt->cmp_fn(key, n->key)>0){
            if(n->r != NULL){
                n = n->r;
            }
            else{
                n->r = node_construct(key, value);
                return;
            }
        }
        else{
            if(bt->keydestroy_fn != NULL){
                bt->keydestroy_fn(key);
            }
            if(bt->valdestroy_fn != NULL){
                bt->valdestroy_fn(value);
            }
            return;
        }

    }

}
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key){
    Node *n = bt->root;
    while(n != NULL){

        if(bt->cmp_fn(key, n->key)==0){
            return n->value;
        }
        if(bt->cmp_fn(key, n->key)<0){
            n = n->l;
        }
        else if(bt->cmp_fn(key, n->key)>0){
            n = n->r;   
        }

    }
    return NULL;
}

void node_destroy_recursive(Node *n, KeyDestroyFn kf, ValDestroyFn vf){
    if(n == NULL){
        return;
    }

    node_destroy_recursive(n->r, kf, vf);
    node_destroy_recursive(n->l, kf, vf);

    if(n->key != NULL && kf != NULL){
        kf(n->key);
    }
    if(n->value != NULL && vf != NULL){
        vf(n->value);
    }

    free(n);

}

void binary_tree_destroy(BinaryTree *bt){
    node_destroy_recursive(bt->root, bt->keydestroy_fn, bt->valdestroy_fn);

    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);