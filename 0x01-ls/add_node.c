#include <stdlib.h>
#include "list.h"

int find_length(char *);

/* add_node takes in two inputs, 1) a pointer to the address of the first node in a list, /list/;
   and 2) a string, /content/, to insert into a new node in the list.

   add_node allocates space for a new node in the list, makes the string inside a copy of
   /content/ and makes the pointer inside a pointer to the previous first node in the list.

   Finally, add_node changes the value of /list/ to the address of the newly-created node, effect-
   ively making the new node the first node of the list.
*/

int add_node(List **list, char *content) {
  struct List *ptr_to_node;
  
  ptr_to_node = malloc(sizeof(struct List));
  if (ptr_to_node == NULL) {
    perror("malloc: ");
    return 2;
  }

  ptr_to_node->str = copy_string(content);
  ptr_to_node->next = *list;
  
  *list = ptr_to_node;
  return 0;
}

/* copy_string finds the length of a given string,
   allocates space for a copy of the string,
   loops through the string to copy its char values into the allocated space,
   and returns the string.
*/
char *copy_string(char *s) {
  int i;
  int length;
  char *copy;

  length = find_length(s);
  copy = malloc(sizeof(char)*length);
  
  for (i = 0; i < length; i++) {
    copy[i] = s[i];
  }

  copy[length - 1] = '\0';

  return copy;
}

/* find_length loops through a given string, incrementing up for every char,
   and returns the length of the string.
*/
int find_length(char *s) {
  int i;
  
  for (i = 0; s[i] != '\0'; i++) {}
  return i;
}
