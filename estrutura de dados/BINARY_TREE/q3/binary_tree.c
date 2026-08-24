#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void *key;
    void *value;
    struct Node *left;
    struct Node *right;
}Node;

struct BinaryTree{
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
    Node *root;
};


BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *bt = (BinaryTree*)calloc(1, sizeof(BinaryTree));
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    bt->root = NULL;

    return bt;
}

Node *node_construct(void *key, void *val){
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->key = key;
    n->value = val;
    n->left = NULL;
    n->right = NULL;

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
            if(n->left != NULL){
                n = n->left;
            }
            else{
                n->left = node_construct(key, value);
                return;
            }
        }
        else if (bt->cmp_fn(key, n->key)>0){
            if(n->right != NULL){
                n = n->right;
            }
            else{
                n->right = node_construct(key, value);
                return;
            }
        }
        else{
            if(bt->key_destroy_fn != NULL){
                bt->key_destroy_fn(key);
            }
            if(bt->val_destroy_fn != NULL){
                bt->val_destroy_fn(value);
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
KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    Node *parent = NULL;
    Node *n = bt->root;

    while(n->left != NULL){
        parent = n;
        n = n->left;
    }

    KeyValPair *kvp = (KeyValPair*)calloc(1, sizeof(KeyValPair));
    kvp->key = n->key;
    kvp->value = n->value;

    if(parent == NULL){
        bt->root = n->right;
    } else{
        parent->left = n->right;
    }
    free(n);

    return kvp;
}
Node *bt_max_rec(Node *n){
    if(n == NULL){
        return NULL;
    }
    else if(n->right == NULL){
        return n;
    }
    else return bt_max_rec(n->right); 
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){

    Node *parent = NULL;
    Node *n = bt->root;
    while(n->right != NULL){
        parent = n;
        n = n->right;
    }
    
    KeyValPair *kvp = (KeyValPair*)calloc(1, sizeof(KeyValPair));
    kvp->key = n->key;
    kvp->value = n->value;

    if(parent == NULL){
        bt->root = n->left;
    } else{
        parent->right = n->left;
    }
    free(n);

    return kvp;
}
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key);

void node_destroy_rec(BinaryTree *bt, Node *n){
    if(n == NULL){
        return;
    }
    node_destroy_rec(bt,n->left);
    node_destroy_rec(bt, n->right);

    if(bt->key_destroy_fn != NULL && n->key != NULL){
        bt->key_destroy_fn(n->key);
    }
    if(bt->val_destroy_fn != NULL && n->value != NULL){
        bt->val_destroy_fn(n->value);
    }

    free(n);
}

void binary_tree_destroy(BinaryTree *bt){
    node_destroy_rec(bt, bt->root);
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