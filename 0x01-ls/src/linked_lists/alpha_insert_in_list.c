#include <stdio.h>
#include "list.h"

/**
 * alpha_insert_in_list - insert a node in an alphabetically sorted link list
 * @list: pointer to pointer to first node in linked list
 * @content: string content for node to insert
 * Return: 0 for error?
 */
int alpha_insert_in_list(List **list, char *content)
{
	int i;
	List *ptr_to_node;
	i = 0;
	ptr_to_node = *list;

	if (ptr_to_node == NULL)
		return (add_node(list, content));

	while (ptr_to_node != NULL && cmpstr(content, ptr_to_node->str) > 0)
	{
		ptr_to_node=ptr_to_node->next;
		i++;
	}
	return (insert_in_list(list, content, i));
}

/**
 * cmpstr - compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 for equivalent strings, the difference between the first characters which differ for nonequivalent strings
 */
int cmpstr(char *s1, const char *s2)
{
	int i;
	i = 0;

	while (s1[i]==s2[i] && s1[i] != '\0')
		i++;
	      
	if (s1[i] == s2[i]) /* str are equivalent */
		return (0); 

	return (s1[i] - s2[i]);
}
