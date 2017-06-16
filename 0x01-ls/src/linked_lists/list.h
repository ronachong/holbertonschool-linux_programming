#ifndef _LIST_H_
#define _LIST_H_

typedef struct List {
  char *str;
  struct List *next;
} List;

int add_node(List **list, char *content);
void free_list(List *list);
int insert_in_list(List **list, char *content, int index);
int list_size(List *list);
List *params_to_list(int ac, char **av);
int print_char(char c);
void print_list(List *list);
void rev_list(List **list);

#endif
