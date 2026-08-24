#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void *key;
    void *value;
    struct Node *l;
    struct Node *r;
}Node;

struct BinaryTree{
    Node *root;
    KeyDestroyFn key_fn;
    ValDestroyFn val_fn;
    CmpFn cmp_fn;
};

Node *node_construct(void *key, void *value){
    Node *n = (Node*)calloc(1, sizeof(Node));
    n->l = NULL;
    n->r = NULL;
    n->key = key;
    n->value = value;

    return n;
}

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);
BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *bt = (BinaryTree*)calloc(1, sizeof(BinaryTree));
    bt->cmp_fn = cmp_fn;
    bt->key_fn = key_destroy_fn;
    bt->val_fn = val_destroy_fn;
    bt->root = NULL;

    return bt;
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
            if(bt->key_fn != NULL){
                bt->key_fn(key);
            }
            if(bt->val_fn != NULL){
                bt->val_fn(value);
            }
            return;
        }
    }
}
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
Node *bt_min_rec(Node *n) {
  if (n == NULL) {
    return NULL;
  }

  if (n->l == NULL) {
    return n;
  } else {
    return bt_min_rec(n->l);
  }
}
void binary_tree_remove_recursive(BinaryTree *bt, Node *n, Node *parent, void *key){

    if (n == NULL) {
        return;
    }

    if (bt->cmp_fn(key, n->key) > 0){
        binary_tree_remove_recursive(bt, n->r, n, key);
    } 
    else if (bt->cmp_fn(key, n->key) < 0) {
        binary_tree_remove_recursive(bt, n->l, n, key);
    } 
    
    else {
        if (n->l == NULL && n->r == NULL) {
            if (parent == NULL) {
                bt->root = NULL;
            } else if (parent->l == n) {
                parent->l = NULL;
            } else {
                parent->r = NULL;
            }
        }

        else if (n->l == NULL) {
            if (parent == NULL) {
                bt->root = n->r;
            } else if (parent->l == n) {
                parent->l = n->r;
            } else {
                parent->r = n->r;
            }
        } 
        
        else if (n->r == NULL) {
            if (parent == NULL) {
                bt->root = n->l;
            } else if (parent->l == n) {
                parent->l = n->l;
            } else {
                parent->r = n->l;
            }
        } 
        else {
            Node *successor = bt_min_rec(n->r);
            void *temp = n->key;
            void *temp2 = n->value;

            n->key = successor->key;
            n->value = successor->value;
            successor->key = temp;
            successor->value = temp2;

            binary_tree_remove_recursive(bt, n->r, n, temp);
            return;
        }
        bt->key_fn(n->key);
        bt->val_fn(n->value);
        free(n);
    }
}

void binary_tree_remove(BinaryTree *bt, void *key){
    binary_tree_remove_recursive(bt, bt->root, NULL, key);
}
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key){
    Node *n = bt->root;
    while(n != NULL){
        if(bt->cmp_fn(key, n->key)<0){
            
            n = n->l;
            
        }
        else if(bt->cmp_fn(key, n->key)>0){
            
            n = n->r;
            
        }
        else{
            return n->value;
        }
    }
    return NULL;
}

void node_recursive_destroy(BinaryTree *bt, Node *n){
    if(n == NULL){
        return;
    }
    node_recursive_destroy(bt, n->l);
    node_recursive_destroy(bt, n->r);
    
    if(bt->key_fn != NULL && n->key != NULL){
        bt->key_fn(n->key);
    }
    if(bt->val_fn != NULL && n->value != NULL){
        bt->val_fn(n->value);
    }
    free(n);
}

void binary_tree_destroy(BinaryTree *bt){
    node_recursive_destroy(bt, bt->root);
    free(bt);
}

void binary_tree_print_recursive(Node *n){
    if(n == NULL){
        printf("NULL");
        return;
    }
    printf("(%d, ", *(int *)n->value);
    binary_tree_print_recursive(n->l);
    printf(", ");
    binary_tree_print_recursive(n->r);
    printf(")");

}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt){
    binary_tree_print_recursive(bt->root);
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);