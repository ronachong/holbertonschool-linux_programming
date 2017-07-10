#include "hashtable.h"
#include <string.h>

List *find_node_in_ht(HashTable *hashtable, const char *key, int i);

/*
 * ht_get takes in the following parameters:
 * 1) a pointer to a hash table @hashtable
 * 2) a string representing a key stored in the hash table, @key
 *
 * ht_get retrieves the index of @key in @hashtable and returns the value corres-
 * ponding to @key within the hash table.
 */
char *ht_get(HashTable *hashtable, const int *key)
{
  int i;
  List *n_ptr;

  /* hash @key to get index, using hash */
  i = hash(key, sizeof(hashtable));
  /* find node in hash table list with @key as key value, using index */
  n_ptr = find_node_in_ht(hashtable, key, i);
  if (n_ptr == NULL)
    return NULL;
  /* else: */
  /* return corresponding value */
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
List *find_node_in_ht(HashTable *hashtable, const char *key, int i)
{
  List *n_ptr;
  n_ptr = hashtable->array[i];

  /* return NULL if list is empty */
  if (n_ptr == NULL)
    return NULL;

  /* identify pointer with key as key element */
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
