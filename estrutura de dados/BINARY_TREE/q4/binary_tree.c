#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *right;
    struct Node *left;
    KeyValPair *kvp;
}Node;

struct BinaryTree{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy;
    ValDestroyFn val_destroy;
};

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = (KeyValPair*)calloc(1, sizeof(KeyValPair));
    kvp->key = key;
    kvp->value = val;

    return kvp;
}
void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp->key);
    free(kvp->value);
    free(kvp);
}

Node *node_construct(void *key, void *value){
    Node *n = (Node*)calloc(1, sizeof(Node));
    KeyValPair *kvp = key_val_pair_construct(key, value);
    n->kvp = kvp;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void node_destroy(Node *n){
    free(n);
}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *bt = (BinaryTree*)calloc(1, sizeof(BinaryTree));
    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy = key_destroy_fn;
    bt->val_destroy = val_destroy_fn;

    return bt;
}
void binary_tree_add(BinaryTree *bt, void *key, void *value){
    if(bt->root == NULL){
        bt->root = node_construct(key, value);
        return;
    }
    Node *n = bt->root;
    while(n != NULL){
        int c = bt->cmp_fn(key, n->kvp->key);
        if(c > 0){
            if(n->right != NULL){
                n = n->right;
            }
            else{
                n->right = node_construct(key, value);
                return;
            }
        }
        else if(c < 0){
            if(n->left != NULL){
                n = n->left;
            }
            else{
                n->left = node_construct(key, value);
                return;
            }
        }
        else{
            bt->key_destroy(key);
            bt->val_destroy(value);
            return;
        }
    }
}
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key){
    Node *atual = bt->root;
    Node *pai = NULL;

    while(atual != NULL){
        int c = bt->cmp_fn(key, atual->kvp->key);
        if(c == 0){
            break;
        } else {
            pai = atual;
            if(c > 0){
                atual = atual->right;
            } else {
                atual = atual->left;
            }
        }
    }
    if(atual == NULL) return;
    if(atual->left != NULL && atual->right != NULL){
        Node *successor_pai = atual;
        Node *successor = atual->right;
        while(successor->left != NULL){
            successor_pai = successor;
            successor = successor->left;
        }
        KeyValPair *temp = atual->kvp;
        atual->kvp = successor->kvp;
        successor->kvp = temp;
        atual = successor;
        pai = successor_pai;
    }
    Node *filho;
    if(atual->left == NULL){
        filho = atual->right;
    } else{
        filho = atual->left;
    }
    if(pai == NULL){
        bt->root = filho;
    } else if(pai->left == atual){
        pai->left = filho;
    } else {
        pai->right = filho;
    }
    key_val_pair_destroy(atual->kvp);
    node_destroy(atual);
}
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);
void *binary_tree_get(BinaryTree *bt, void *key);

void node_destroy_rec(Node *n){
    if(n == NULL){
        return;
    }

    key_val_pair_destroy(n->kvp);

    node_destroy_rec(n->left);
    
    node_destroy_rec(n->right);
    
    node_destroy(n);
}
void binary_tree_destroy(BinaryTree *bt){
    node_destroy_rec(bt->root);
    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

void inorder(Node *n, Vector *v){
    if(n == NULL){
        return;
    }
    inorder(n->left, v);
    vector_push_back(v, n->kvp);
    inorder(n->right, v);
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){
    Vector *v = vector_construct();
    inorder(bt->root, v);
    return v;
}

void preorder(Node *n, Vector *v){
    if(n == NULL){
        return;
    }
    vector_push_back(v, n->kvp);
    preorder(n->left, v);
    preorder(n->right, v);
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){
    Vector *v = vector_construct();
    preorder(bt->root, v);

    return v;
}

void postorder(Node *n, Vector *v){
    if(n == NULL) return;
    postorder(n->left, v);
    postorder(n->right, v);
    vector_push_back(v, n->kvp);
}
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt){
    Vector *v = vector_construct();
    postorder(bt->root, v);

    return v;
}