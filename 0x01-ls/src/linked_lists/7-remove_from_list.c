#include <stdlib.h>
#include "list.h"

int add_node(List **list, char *str);
List *find_node_prior(List *, int);
int insert_new_node(List *, char *content, List*);
char *copy_string(char *);
void print_string(char *);

int remove_from_list(List **list, int index) {
  List *ptr_to_node_prior;
  List *ptr_to_node_to_free;
  List *ptr_to_node_after;

  /* handle index parameter less than 0 or empty list */
  if (index < 0 || *list == NULL) {
    return 0;
  }
  
  /* else, if index parameter 0 */
  if (index == 0) {
    /* simply free string in node and node itself */
    ptr_to_node_to_free = *list;
    ptr_to_node_after = ptr_to_node_to_free->next;
    free(ptr_to_node_to_free->str);
    free(ptr_to_node_to_free);

    /* make node after the new head*/
    *list = ptr_to_node_after;
    return 1;
  }

  /* ELSE */
  /* find the node prior to node we want to insert */
  ptr_to_node_prior = find_node_prior(*list, index);

  /* if index req'd greater than size of list */
  if (ptr_to_node_prior == NULL) {
    return 0;
  }

  /* if not */
  ptr_to_node_to_free = ptr_to_node_prior->next;
  ptr_to_node_after = ptr_to_node_to_free->next;

  /* free string in node */
  free(ptr_to_node_to_free->str);

  /* free node itself */
  free(ptr_to_node_to_free);

  /* make prior node point to node after free'd node */
  ptr_to_node_prior->next = ptr_to_node_after;

  return 1;
}


List *find_node_prior(List *ptr_to_head, int index) {
  int i;
  List *current_node_ptr;

  for (i = 0, current_node_ptr = ptr_to_head; i < index; i++) {
    /* if i is one less than the index of node to insert, we've found
       the node prior; return! */
    if (i == index - 1) {
      return current_node_ptr;
    }
    
    /* else */
    /* update current node to next node */
    current_node_ptr = current_node_ptr->next;
  }

  /* if loop did not succeed... then probably index req'd
     is greater than size of list*/
  return NULL;
}
