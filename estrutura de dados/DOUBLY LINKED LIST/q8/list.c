#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Construct a new double linked list object
 *  Allocates memory for a new double linked list and returns a pointer to it.
 * @return List*
 * Pointer to the newly allocated double linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the double linked list using list_destroy().
 *
 */
List *list_construct(){
    List *l = (List*)calloc(1, sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

/**
 * @brief Returns the size of the double linked list.
 *  Returns the number of nodes in the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @return int
 * Number of nodes in the double linked list.
 *
 */
int list_size(List *l);

/**
 * @brief Pushes a new node to the front of the double linked list.
 *  Allocates memory for a new node and inserts it at the front of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void list_push_front(List *l, data_type data);

/**
 * @brief Pushes a new node to the back of the double linked list.
 *
 * @param l
 * Pointer to the double linked list.
 * @param data
 * data to be stored in the new node.
 */
void list_push_back(List *l, data_type data){
    Node *new_node = node_construct(data, l->last, NULL);
    if(l->last == NULL){
        l->head = new_node;
        l->last = new_node; 
    } else {
        l->last->next = new_node;
        l->last = new_node;
    }
    l->size++;
}

/**
 * @brief Print the elements of the double linked list.
 *  Print the elements of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void list_print(List *l, void (*print_fn)(data_type));

/**
 * @brief Print the elements of the double linked list in reverse order.
 * Print the elements of the double linked list in reverse order.
 * @param l
 * Pointer to the double linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 */
void list_print_reverse(List *l, void (*print_fn)(data_type));

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the double linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type list_get(List *l, int i);

/**
 * @brief Remove the first node of the double linked list and returns its data.
 * @param l
 * Pointer to the double linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the double linked list that was removed.
 *
 */
data_type list_pop_front(List *l);

/**
 * @brief Remove the last node of the double linked list and returns its data.
 * @param l
 * Pointer to the double linked list.
 * @return data_type
 * Data stored in the last node of the double linked list that was removed.
 */
data_type list_pop_back(List *l);

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the double linked list.
 * @return List*
 * Pointer to the newly allocated double linked list.
 */
List *list_reverse(List *l);

/**
 * @brief Removes all nodes from the double linked list.
 * Removes all nodes from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void list_clear(List *l);

/**
 * @brief Removes all nodes with the given value from the double linked list.
 * Removes all nodes with the given value from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @param val
 * Value to be removed from the double linked list.
 */
void list_remove(List *l, data_type val);

/**
 * @brief Removes all duplicate values from the double linked list.
 * Removes all duplicate values from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @note
 * The double linked list must be sorted.
 */
void list_unique(List *l);

/**
 * @brief Adds all nodes from the given list to the end of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @param m
 * Pointer to the double linked list to be added to the end of the double linked list.
 */
void list_cat(List *l, List *m);

/**
 * @brief Sorts the double linked list.
 * Sorts the double linked list.
 * @param l
 * Pointer to the double linked list.
 */
void list_sort(List *l);

/**
 * @brief Destroys the double linked list.
 *  Frees the memory allocated for the double linked list and all its nodes.
 * @param l
 * Pointer to the double linked list.
 *
 */
void list_destroy(List *l){
    Node *current=l->head;
    while(current != NULL){
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

/**
 * @brief Returns an iterator to the first node of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @return ListIterator*
 * Pointer to the iterator.
 */
ListIterator *list_front_iterator(List *l){
    ListIterator *li = (ListIterator*)calloc(1, sizeof(ListIterator));
    li->current = l->head;
    return li;
}

/**
 * @brief Returns an iterator to the last node of the double linked list.
 * @param l
 * Pointer to the double linked list.
 * @return ListIterator*
 * Pointer to the iterator.
 */
ListIterator *list_back_iterator(List *l){
    ListIterator *li = (ListIterator*)calloc(1, sizeof(ListIterator));
    li->current = l->last;
    return li;
}


/**
 * @brief Returns the data stored in the node and updates the iterator to point to the next node.
 * @param it
 * Pointer to the iterator.
 * @return data_type*
 * Pointer to the data stored in the current node.
 */
data_type *list_iterator_next(ListIterator *it){
    data_type *data = &(it->current->value);
    it->current = it->current->next;

    return data;
}

/**
 * @brief Returns the data stored in the node and updates the iterator to point to the previous node.
 * @param it
 * Pointer to the iterator.
 * @return data_type*
 * Pointer to the data stored in the current node.
 */
data_type *list_iterator_previous(ListIterator *it){

    data_type *data = &(it->current->value);
    it->current = it->current->last;

    return data;
}

/**
 * @brief Returns true if the iterator is over.
 * @param it
 * Pointer to the iterator.
 * @return 1 if the iterator is over, and 0 otherwise.
 */
int list_iterator_is_over(ListIterator *it){
    if(it->current == NULL){
        return 1;
    }
    return 0;
}

/**
 * @brief Free the memory allocated to the iterator.
 * @param it
 * Pointer to the iterator.
 */
void list_iterator_destroy(ListIterator *it){
    free(it);
}