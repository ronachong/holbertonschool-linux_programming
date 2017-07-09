#include "hashtable.h"
#include <stdlib.h>

/*
 * ht_create takes in the unsigned int "size" for its parameter and returns
 * a pointer to a HashTable struct with an array containing "size" cells.
 * In essence, ht_create creates a hash table of size "size."
 */

HashTable *ht_create(unsigned int size)
{
  HashTable *ht_ptr;
  List **array;

  /* create HashTable struct using malloc */
  ht_ptr = malloc(sizeof(HashTable));
  /* create array for HashTable using malloc */
  array = malloc(sizeof(List *)*size);
  /* assign value for size element of HashTable */
  ht_ptr->size = size;
  /* assign array to HashTable */
  ht_ptr->array = array;

  return ht_ptr;
}
