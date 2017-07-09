#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

List *add_as_head(List *l_ptr, const char *key, const char *value);
List *find_node_in_ht0(HashTable *hashtable, const char *key, int i);

/*
 * ht_put takes in the following three parameters:
 * 1) the pointer @hashtable, pointing to a hash table
 * 2) the string @key, to be hashed
 * 3) the string @value, which is the value corresponding to @key
 *
 * ht_put hashes @key, creates and adds a linked list node containing @key and
 * @value to the hash table pointed to by @hashtable, and returns 0 upon suc-
 * cess, 1 upon error.
 */

int ht_put(HashTable *hashtable, const char *key, const char *value)
{
  int i;
  List *n_ptr;

  /* hash @key and get index, using hash */
  i = hash(key,  sizeof(hashtable));

  /* if key exists in hash table, replace value with value passed as arg */
  n_ptr = find_node_in_ht0(hashtable, key, i);
  if (n_ptr != NULL) {
    free(n_ptr->value);
    n_ptr->value = strdup(value);
    return 0;
  }  

  /* else */
  /* create linked list node with @key and @value */
  n_ptr = add_as_head(hashtable->array[i], key, value);
  /* if mem alloc failed */
  if (n_ptr == NULL) {
    return 1;
  }
  /* else: */
  /* add new node to hash table at index */
  hashtable->array[i] = n_ptr;
  /* return index of key and value pair in hash table */
  return 0;
}


/*
 * add_as_head takes in the following inputs:
 * 1) the pointer to the head of a list in a hash table, @l_ptr
 * 2) the string @key
 * 3) the string @value, which is the value corresponding to @key
 *
 * add_as_head creates a new List node with a copy of @key as its key element,
 * a cpopy of @value as its value element, and the former head of the list
 * pointed to by @l_ptr as its next element.
 * finally, add_as_head returns the pointer to the new node.
 */
List *add_as_head(List *l_ptr, const char *key, const char *value)
{
  List *n_ptr;

  /* create List node using malloc */
  n_ptr = malloc(sizeof(List));
  if (n_ptr == NULL) {
    return NULL;
  }
  /* assign key value using strdup */
  n_ptr->key = strdup(key);
  /* assign value value using strdup */
  n_ptr->value = strdup(value);
  if (n_ptr->key == NULL || n_ptr->value == NULL) {
    return NULL;
  }
  /* assign next value using @l_ptr */
  n_ptr->next = l_ptr;
  /* return pointer to List node */
  return n_ptr;
}


/*
 * find_node_in_ht takes in the following parameters:
 * 1) a pointer to a hash table @hashtable
 * 2) a string representing a key stored in the hash table, @key
 * 3) an integer representing the index of the key in the hash table, @i
 *
 * find_node_in_ht searches the linked list at the @i in the hashtable
 * and returns the pointer to the node containing @key as its key element.
 */
List *find_node_in_ht0(HashTable *hashtable, const char *key, int i)
{
  List *n_ptr;
  n_ptr = hashtable->array[i];

  /* if list is empty, return NULL */
  if (n_ptr == NULL)
    return NULL;

  /* else, identify pointer with key as key element */
  while (n_ptr->key != key) {
    n_ptr = n_ptr->next;
    /* return NULL if end of list is reached */
    if (n_ptr == NULL) {
      return NULL;
    }
  }
  /* else: */
  return n_ptr;
}

