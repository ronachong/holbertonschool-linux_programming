#include <stdlib.h>
#include "list.h"

/* rev_list takes in a pointer to the addr of the head of a list and
   reverses the order of the list by making each node point to its
   predecessor; and updating the pointer to the head to point to the
   last node.
*/

void rev_list(List **list) {
  List *prev_node_ptr;
  List *current_node_ptr;
  List *next_node_ptr;

  /* do nothing if list is empty */
  if (*list == NULL) {
    return;
  }

  /* else */
  /* initialize the pointer to previous node to NULL
     & current node to first node in list */
  prev_node_ptr = NULL;
  current_node_ptr = *list;

  /* for every node till the last node */
  while (current_node_ptr->next != NULL) {

    /* store pointer to next node */
    next_node_ptr = current_node_ptr->next;

    /* make current node point to prior node */
    current_node_ptr->next = prev_node_ptr;

    /* update previous node to be current node
       & current node to be next node */
    prev_node_ptr = current_node_ptr;
    current_node_ptr = next_node_ptr;
  }

  /* make last node point to prior node */
  current_node_ptr->next = prev_node_ptr;  

  /* change the pointer to the first node to point to
     last node */
  *list = current_node_ptr;
}
