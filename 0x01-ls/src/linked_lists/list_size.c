#include <stdlib.h>
#include "list.h"

/* list_size loops thru the list pointed to by list and                                                 
   increments up for every node in list, returning the                                                  
   size of the list                                                                                    
*/
int list_size(List *list) {
  int i;
  struct List *ptr_to_node;

  /* initialize ptr to node as ptr to the head of the list */
  ptr_to_node = list;

  /* count up each time a node does not point to NULL */
  for (i = 0; ptr_to_node->next != NULL; i++) {
    ptr_to_node = ptr_to_node->next;
  }

  /* count last node */
  i++;
  
  /* return count */
  return i;
}

