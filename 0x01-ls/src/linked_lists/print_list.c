#include <stdlib.h>
#include "list.h"

int print_char(char);
void print_string(char *s);

/* print_every_string_in_list loops thru the list pointed to by                                             
   ptr_to_head_of_list and prints the string in each node */
void print_list(List *list) {
  struct List *ptr_to_node;

  /* if list is empty!! */
  if (list == NULL) {
    print_char('\n');
    return;
  }

  /* initialize ptr to node as ptr to the head of the list */
  ptr_to_node = list;

  /* print string, followed by comma and space, for every node but last */
  while (ptr_to_node->next != NULL) {
    print_string(ptr_to_node->str);
    print_char(',');
    print_char(' ');
    ptr_to_node = ptr_to_node->next;
  }

  /* print string in last node, followed by new line */
  print_string(ptr_to_node->str);
  print_char('\n');
}

/* print_string loops thru string input and prints every
   char using print_char */
void print_string(char *s) {
  int i;
  
  for (i = 0; s[i] != '\0'; i++) {
    print_char(s[i]);
  }
}
