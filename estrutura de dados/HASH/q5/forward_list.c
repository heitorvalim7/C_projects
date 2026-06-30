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
    ForwardList *l = (ForwardList*)calloc(1, sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;

    return l;
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
    return l ->size;
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
    Node *new_node = node_construct(data, l->head);
    l->head = new_node;
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
    Node *current = l->head;
    while(current != NULL){
        print_fn(current->value);
        current = current->next;
    }
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
    if(i < 0 || i>= l->size){
        return NULL;
    }
    Node *current = l->head;
    for(int j = 0; j<i; j++){
        current = current->next;
    }
    return current->value;
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
    if(l->size == 0){
        return NULL;
    }
    Node *temp = l->head;
    data_type value = temp->value;
    l->head = l->head->next;
    node_destroy(temp);
    l->size--;

    return value;
}

/**
 * @brief Remove the node in the given index.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the removed node.
 *
 */
data_type forward_list_pop_index(ForwardList *l, int index){
    if(index < 0 || index>= l->size){
        printf("INVALID INDEX\n");
        return NULL;
    }
    if(index == 0){
        return forward_list_pop_front(l);
    }
    Node *current = l->head;
    for(int i = 0; i<index-1; i++){
        current = current->next;
    }
    Node *temp = current->next;
    data_type value = temp->value;
    current ->next = temp->next;
    node_destroy(temp);
    l->size--;
    return value;
}

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
ForwardList *forward_list_reverse(ForwardList *l);

/**
 * @brief Removes all nodes from the linked list.
 * Removes all nodes from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void forward_list_clear(ForwardList *l);

/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val);

/**
 * @brief Removes all duplicate values from the linked list.
 * Removes all duplicate values from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The linked list must be sorted.
 */
void forward_list_unique(ForwardList *l);

/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 */
void forward_list_cat(ForwardList *l, ForwardList *m);

/**
 * @brief Sorts the linked list.
 * Sorts the linked list.
 * @param l
 * Pointer to the linked list.
 */
void forward_list_sort(ForwardList *l){

    ForwardList *sorted = forward_list_construct();
    while(l->size > 0){
        data_type min = forward_list_get(l, 0);
        int min_data = *(int*)min;
        int min_index = 0;
        for(int i = 1; i<l->size; i++){
            data_type current = forward_list_get(l, i);
            int current_data = *(int*)current;
            if(current_data < min_data){
                min_data = current_data;
                min_index = i;
            }
        }
        forward_list_push_front(sorted, forward_list_pop_index(l, min_index));
    }
    
    while(sorted->size > 0){
        forward_list_push_front(l, forward_list_pop_front(sorted));
    }
    forward_list_destroy(sorted);
}

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 */
void forward_list_destroy(ForwardList *l){
    Node *current = l->head;
    while(current != NULL){
        Node *temp = current;
        current = current->next;
        node_destroy(temp);
    }
    free(l);
}
