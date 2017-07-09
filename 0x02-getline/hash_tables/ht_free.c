#include "hashtable.h"
#include <stdlib.h>

/*
 * ht_free takes in as its parameter the point to a hashtable @hashtable.
 * ht_free frees all of the strings in each List within the hash table,
 * then the Lists, then array element of the hash table, then the hash table
 * struct itself.
 */
void ht_free(HashTable *hashtable)
{
  unsigned int i;
  List *n_ptr;
  List *tmp;

  for (i = 0; i < hashtable->size; i++) {
    n_ptr = hashtable->array[i];
    while (n_ptr != NULL) {
      /* free alloced node contents, then each node in list at index */
      free(n_ptr->key);
      free(n_ptr->value);
      tmp = n_ptr->next;
      free(n_ptr);
      /* move on to next node */
      n_ptr = tmp;
    }
  }
  /* free array of hash table */
  free(hashtable->array);
  /* free hash table */
  free(hashtable);
}
