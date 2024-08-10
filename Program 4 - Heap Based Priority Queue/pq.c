/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/* COMPLETED
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* values;
  struct dynarray* priority;
};


/* COMPLETED
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq *new = malloc(sizeof(struct pq));
  new->values = dynarray_create();
  new->priority = dynarray_create();

  return new;
}


/* COMPLETED
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->values);
  dynarray_free(pq->priority);
  free(pq);
  return;
}


/* COMPLETED
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  return (dynarray_size(pq->values) == 0)? 1 : 0;
}


/* COMPLETED
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  int *c_pvalue = (int*)malloc(sizeof(int));
  *c_pvalue = priority;
  
  dynarray_insert(pq->values, value);
  dynarray_insert(pq->priority, c_pvalue);

  int c_index = dynarray_size(pq->priority) - 1;
  int p_index = (c_index - 1)/2;
  int *p_pvalue = dynarray_get(pq->priority, p_index);
  void *temp;

  do{  
    if (*p_pvalue > priority){
      temp = dynarray_get(pq->priority, p_index);
      dynarray_set(pq->priority, p_index, c_pvalue);
      dynarray_set(pq->priority, c_index, temp);
    
      temp = dynarray_get(pq->values, p_index);
      dynarray_set(pq->values, p_index, value);
      dynarray_set(pq->values, c_index, temp);
    }
  
    c_index = p_index;
    p_index = (p_index - 1)/2;
    p_pvalue = dynarray_get(pq->priority, p_index);
    
  } while(c_index != 0);

  return;
}


/* COMPLETED
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  if (pq_isempty(pq) == 0){
    return dynarray_get(pq->values, 0);
  }

  return NULL;
}


/* COMPLETED
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  if (pq_isempty(pq) == 0){
    int *priority_value = dynarray_get(pq->priority, 0);
    return *priority_value;
  }

  return 0;
}


/* COMPLETED
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  if (pq_isempty(pq) == 0){
    int c_index = dynarray_size(pq->priority) - 1;
    int p_index = 0;
    int r_child = 2;
    int l_child = 1;
    int *p_pvalue;
    int *l_child_pvalue;
    int *r_child_pvalue;
    int *l_child_value;
    int *r_child_value;
    void *temp;

    // gets the root value to be returned
    void *root = pq_first(pq);

    // overriding the first value with the last element
    dynarray_set(pq->values, 0, dynarray_get(pq->values, c_index));
    value_freer(pq->priority, 0);
    dynarray_set(pq->priority, 0, dynarray_get(pq->priority, c_index));

    // entering the while loop if at least the left child exists
    while((dynarray_size(pq->values) - 1) >= l_child){

      // if both a left and right child exist
      if(dynarray_size(pq->values) - 1 >= r_child ){
        
        // getting the values for both left / right children and parent
        l_child_pvalue = dynarray_get(pq->priority, l_child);
        r_child_pvalue = dynarray_get(pq->priority, r_child);
        l_child_value = dynarray_get(pq->values, l_child);
        r_child_value = dynarray_get(pq->values, r_child);
        p_pvalue = dynarray_get(pq->priority, p_index);

        // determining whether left or right child is less in value
        // if the left is less
        
        if (*l_child_pvalue < *r_child_pvalue){
          if (*p_pvalue > *l_child_pvalue){
            temp = dynarray_get(pq->priority, p_index);
            dynarray_set(pq->priority, p_index, l_child_pvalue);
            dynarray_set(pq->priority, l_child, temp);
          

            temp = dynarray_get(pq->values, p_index);
            dynarray_set(pq->values, p_index, l_child_value);
            dynarray_set(pq->values, l_child, temp);

            p_index = l_child;
          }
        } 
        // if the right is less or equal
        else if (*l_child_pvalue >= *r_child_pvalue){
          if (*p_pvalue > *r_child_pvalue){
            temp = dynarray_get(pq->priority, p_index);
            dynarray_set(pq->priority, p_index, r_child_pvalue);
            dynarray_set(pq->priority, r_child, temp);
          

            temp = dynarray_get(pq->values, p_index);
            dynarray_set(pq->values, p_index, r_child_value);
            dynarray_set(pq->values, r_child, temp);

            p_index = r_child;
          }
        }
      } 
      
      // if only a left child exists
      else{
        l_child_pvalue = dynarray_get(pq->priority, l_child);
        l_child_value = dynarray_get(pq->values, l_child);
        p_pvalue = dynarray_get(pq->priority, p_index);

        if (*p_pvalue > *l_child_pvalue){
          temp = dynarray_get(pq->priority, p_index);
          dynarray_set(pq->priority, p_index, l_child_pvalue);
          dynarray_set(pq->priority, l_child, temp);
        

          temp = dynarray_get(pq->values, p_index);
          dynarray_set(pq->values, p_index, l_child_value);
          dynarray_set(pq->values, l_child, temp);

          p_index = l_child;
        }
      }
      
      

      // if neither child is less than the parent, then this forces the parent's index out of bounds
      if (p_index != r_child && p_index != l_child){
        p_index = dynarray_size(pq->values) + 3;
      }

      r_child = 2 * p_index + 1;
      l_child = 2 * p_index + 2;
    }

    // removing the last value
    dynarray_remove(pq->values, c_index);
    dynarray_remove(pq->priority, c_index);
    
    return root;
  }

  return NULL;
}
