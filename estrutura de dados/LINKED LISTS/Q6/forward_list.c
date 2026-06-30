#include "forward_list.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>



/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 *
 */
ForwardList *forward_list_construct(){
    ForwardList *fl = (ForwardList*)calloc(1, sizeof(ForwardList));
    fl->head = NULL;
    fl->size = 0;

    return fl;
}
/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void forward_list_push_front(ForwardList *l, data_type data){
    l->head = node_construct(data, l->head);
    l->size++;
}

/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *n = l->head;
    printf("[");
    while(n != NULL){
        print_fn(n->value);
        n = n->next;
        if(n != NULL){
            printf(", ");
        }
    }
    printf("]");
}

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 */
void forward_list_destroy(ForwardList *l){
    while(l->head != NULL){
        Node *temp = node_next(l->head);
        free(l->head);
        l->head = temp;    
    }
    free(l);
}
/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 *
 */
int forward_list_size(ForwardList *l){
    return l->size;
}
/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 */
data_type forward_list_pop_front(ForwardList *l){
    data_type n = node_value(l->head);
    Node *next = node_next(l->head);
    node_destroy(l->head);
    l->size--;
    l->head = next;
    return n;
}

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type forward_list_get(ForwardList *l, int i){
    if(i > l->size){
        return -1;
    }

    Node *n = l->head;

    for(int j = 0; j<i; j++){
        n = n->next;
    }

    return n->value;
}
/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val){

    Node *next = l->head;
    Node *previous = NULL;

    while(next != NULL){
        Node *remove;
        if(next->value == val){
            if(next == l->head){
                l->head = next->next;
                remove = next;
                next = l->head;
                node_destroy(remove);
                l->size--;
            }
            else{
                previous->next = next->next;
                remove = next;
                next = next->next;
                node_destroy(remove);
                l->size--;
            } 
        }
        else{
            previous = next;
            next = next->next;
        }
    }
    
}

/**
 * @brief Removes all nodes from the linked list.
 * Removes all nodes from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void forward_list_clear(ForwardList *l){
    Node *next = l->head;

    while(next != NULL){
        Node *remove;
        
        l->head = next->next;
        remove = next;
        next = l->head;
        node_destroy(remove);
        l->size--;
    }
}
/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 */
void forward_list_cat(ForwardList *l, ForwardList *m){
    while(m->head != NULL){
        data_type valuem = forward_list_pop_front(m);
        forward_list_push_front(l, valuem);
    }
}