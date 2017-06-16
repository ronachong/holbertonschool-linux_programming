#include <stdlib.h>
#include "list.h"

int add_node(List **, char *);
char *copy_string(char *);
int find_length(char *);
struct List *find_end_of_list(struct List **);

/* params_to_list takes in an array of string arguments /av/,
   creates a list with a node for each string arg,
   and returns the pointer to the first node of the list.

   A more detailed breakdown:
   params_to_list
   1) creates a pointer for the head of the list & makes this equal to NULL (temporarily);
   2) then, calls add_node (which:
      - uses malloc to allocate space for a new node and create a pointer to the memory;
      - uses malloc to allocate space for a copy of the string arg;
      - uses copy_string to copy the char values of the string arg to the memory for the copy;
      - uses the pointer to the new node to assign the copy string to the node;
      - & makes the next pointer of the previous node (i.e. the current tail of the list) point
        to the new node, using find_end_of_list
	UNLESS the new node happens to be the only node for the list so far, in which case,
	params_to_list changes the header pointer to point to the new node.)
      for every string element in /av/
   3) finally, params_to_list returns the head pointer.
*/

List *params_to_list(int ac, char **av) {
  int i;
  struct List *ptr_to_head;

  ptr_to_head = NULL;
  for (i = 1; i < ac; i++) {
    add_node(&ptr_to_head, av[i]);
  }

  return ptr_to_head;
}



/* add_node takes in two inputs, 1) a pointer to the address of the first node in a list, /list/;           
   and 2) a string, /content/, to insert into a new node in the list.                                       
                                                                                                            
   add_node allocates space for a new node in the list, makes the string inside the node a copy of          
   /content/ and makes the /next/ pointer inside the node a pointer to NULL (tail of list).                 
                                                                                                            
   Finally, add_node changes the /next/ pointer of the current tail node of the list to point to            
   the new node, effectively making making the new node the new last node of the list.                      
*/

int add_node(List **list, char *content) {
  struct List *ptr_to_node;
  struct List *ptr_to_current_tail;

  ptr_to_node = malloc(sizeof(struct List));
  if (ptr_to_node == NULL) {
    return 1;
  }

  ptr_to_node->str = copy_string(content);
  ptr_to_node->next = NULL;

  /* if list is NULL (i.e. list is empty) */
  if (*list == NULL) {
    /* make list point to ptr_to_node */
    *list = ptr_to_node;
    return 0;
  }

  /* ELSE */
  /* find current tail node in list and make it point to newly-allocated node instead of NULL. */
  ptr_to_current_tail = find_end_of_list(list);
  ptr_to_current_tail->next = ptr_to_node;

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



/* find_end_of_list takes the pointer to the head of a list, /list/,                                        
   and proceeds to the /next/ pointer in each node in the list,                                             
   until it reaches a NULL pointer.                                                                         
                                                                                                            
   It returns the pointer to the current last node in the list.                                             
*/
struct List *find_end_of_list(struct List **list) {
  struct List *ptr_to_node;

  /* initialize ptr to node as ptr to the head of the list */
  ptr_to_node = *list;

  while (ptr_to_node->next != NULL) {
    ptr_to_node = ptr_to_node->next;
  }

  return ptr_to_node;
}
