/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Santosh Ramesh
 * Email: rameshsa@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "stack.h"

/* COMPLETED
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/* COMPLETED
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/* COMPLETED
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst *new = malloc(sizeof(struct bst));
  new->root = NULL;
  return new;
}

/* COMPLETED
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  if (bst->root == NULL){
    return;
  } else{
    freer(bst->root);
  }

  free(bst);
}

void freer(struct bst_node* node){
  if (node->left != NULL){
    freer(node->left);
  }
  if (node->right != NULL){
    freer(node->right);
  }
  free(node);
  return;
}

/* COMPLETED
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  int size = 0;
  if (bst->root == NULL){
    return 0;
  } else{
    size_counter(bst->root, &size);
    return size;
  }
  
}

void size_counter(struct bst_node* node, int* size){
  (*size)++;
  if (node->left != NULL){
    
    size_counter(node->left, size);
  }
  if (node->right != NULL){
    size_counter(node->right, size);
  }
  return;
}

/* COMPLETED
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  struct bst_node *P = NULL;
  struct bst_node *N = bst->root;
  
  while (N != NULL){
    P = N;
    if (key < N->key){
      N = N->left;
    }else{
      N = N->right;
    }
  }

  // creating the new node:
  struct bst_node *new = malloc(sizeof(struct bst_node));
  new->left = NULL;
  new->right = NULL;
  new->key = key;
  new->value = value;

  // assigning node to child of parent
  if (bst->root == NULL){
    bst->root = new;
  } else if (key < P->key){
    P->left = new;
  } else{
    P->right = new;
  }
  
  return;
}

/* COMPLETED
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  struct bst_node *N = bst->root;
  struct bst_node *P = NULL;
  
  // finding N & P
  while (N != NULL && N->key != key){
    P = N;
    if (key < N->key){
      N = N->left;
    }else{
      N = N->right;
    }
  }

  // ending the function if the value to be removed can't be found
  if (N == NULL){
    return;
  }
  
  // if statements to determine what to do based on number of children
  if (N->left == NULL && N->right == NULL){
    if (key < P->key){
      P->left = NULL;
    }else{
      P->right = NULL;
    }
    free(N);
  } else if (N->left == NULL || N->right == NULL) {
    if (key < P->key){
      if(N->left == NULL){
        P->left = N->right;
      } else{
        P->left = N->left;
      }
    }else{
      if(N->left == NULL){
        P->right = N->right;
      } else{
        P->right = N->left;
      }
    }
    free(N);
  }else{
    struct bst_node *S = N;
    struct bst_node *SP = P;
    
    // finding S & SP (successor and successor parent)
    SP = S;
    S = S->right;
    
    while (S->left != NULL){
      SP = S;
      S = S->left;
    }

    S->left = N->left;
    
    if (S != N->right){
      SP->left = S->right;
      S->right = N->right;
    }
    
    if (bst->root == N){
      bst->root = S;
    } 
    
    else{
      if (key < P->key){
        P->left = S;
      }else{
        P->right = S;
      }
    }
    free(N);

  }
  return;
}

/* COMPLETED
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node *N = bst->root;
  
  while (N != NULL){
    if (key == N->key){
      return N->value;
    }
    else if(key < N->key){
      N = N->left;
    }else{
      N = N->right;
    }
  }

  return NULL;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/* COMPLETED
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/* MODIFIED
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  struct bst_iterator *new = malloc(sizeof(struct bst_iterator));
  new->stack = stack_create();
  stack_add(bst->root, new);
  return new;
}

void stack_add(struct bst_node *node, struct bst_iterator *iter){
  if(node != NULL){
    stack_add(node->right, iter);
    stack_push(iter->stack, node);
    stack_add(node->left, iter);
  }
}

/* MODIFIED
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  stack_free(iter->stack);
  free(iter);
  return;
}

/* MODIFIED
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  if (stack_isempty(iter->stack) == 1){
    return 0; 
  } else{
    return 1;
  }
}

/* INCOMPLETE
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  struct bst_node *current = stack_pop(iter->stack);
  *value = current->value;
  return current->key;
}
