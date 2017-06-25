#include <stdio.h>
#include "list.h"
#include "hls-components.h"

/**
 * f_is_hidden - determins if file is a hidden file
 * @fname: name of file
 *
 * Return: 1 if file is a hidden file, 0 if not
 */
int f_is_hidden(char *fname)
{
	if (fname[0] == '.' &&
	    cmpstr(fname, ".") != 0 &&
	    cmpstr(fname, "..") != 0)
		return (1);
	return (0);

}

/**
 * fname_precedes - determines whether node 1 should precede node 2
 * @fname1: file name for node 1
 * @fname2: file name for node 2
 *
 * Return: 1 if node with @fname1 should precede node w/ @fname2
 */
int fname_precedes(char *fname1, char *fname2)
{
	int ret;

	if (f_is_hidden(fname1))
	{
		if (f_is_hidden(fname2))
		{
			while (fname1[0] == '.')
				fname1++;
			while (fname2[0] == '.')
				fname2++;
			ret = (cmpstr_ls(fname1, fname2) < 0) ? 1:0;
		}
		else
			ret = 0;
	}
	else
	{
		if (f_is_hidden(fname2))
			ret = 1;
		else
			ret = (cmpstr_ls(fname1, fname2) < 0) ? 1:0;
	}
	return (ret);
}

/**
 * alpha_insert_in_list - insert a node in an alphabetically sorted link list
 * @list: pointer to pointer to first node in linked list
 * @content: string content for node to insert
 * Return: 0 for success, 2 for malloc error
 */
int alpha_insert_in_list(List **list, char *content)
{
	int i;
	List *ptr_to_node;
	/* char *fname1; */
	/* char *fname2; */
		

	/* printf("DB: -- alpha_insert_in_list\n"); */

	i = 0;
	ptr_to_node = *list;

	if (ptr_to_node == NULL)
		return (add_node(list, content));

	while (ptr_to_node != NULL)
	{
		if (fname_precedes(content, ptr_to_node->str))
			break;					 
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
