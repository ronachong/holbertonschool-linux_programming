#include "hashtable.h"
#include <stdio.h>

HashTable *ht_create(unsigned int size);
int ht_put(HashTable *hashtable, const char *key, const char *value);
char *ht_get(HashTable *hashtable, const char *key);
unsigned int hash(const char *key, unsigned int size);
void ht_free(HashTable *hashtable);
int print_hashtable(HashTable *ht);

int main(void) {
  HashTable *ht = ht_create(5);
  ht_put(ht, "One", "Value One");
  ht_put(ht, "Two", "Value Two");
  ht_put(ht, "Three", "Value Three");
  ht_put(ht, "Four", "Value Four");
  ht_put(ht, "Five", "Value Five");
  ht_put(ht, "Six", "Value Six");
  ht_put(ht, "Seven", "Value Nine");
  print_hashtable(ht);
  ht_free(ht);
  return 0;
}

int print_hashtable(HashTable *ht) {
  unsigned int i = 0;
  List *listptr;
  for ( ; i<ht->size ; i++) {
    printf("%d\n", i);
    /* traverse list */
    listptr = ht->array[i];
    printf("\t--------\n");
    while (listptr != NULL) {
      printf("\tkey: %s\n\tval: %s\n", listptr->key, listptr->value);
      printf("\tht_get finds: %s\n", ht_get(ht, listptr->key));
      printf("\t--------\n");
      listptr = listptr->next;
    }
    printf("\tNULL\n\t--------\n");
  }
  return 0;
}
