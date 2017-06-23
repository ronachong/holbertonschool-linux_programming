#include "hls-components.h"

/**
 * cmpstr_ls - compare two strings for ls
 * @s1: first string
 * @s2: second string
 * Return: 0 for equivalent strings, the difference between the first characters which differ for nonequivalent strings
 */
int cmpstr_ls(char *s1, const char *s2)
{
	int i;
	i = 0;

	while (get_snum(s1[i])==get_snum(s2[i])
	       && s1[i] != '\0')
		i++;
	      
	if (s1[i] == s2[i]) /* str are equivalent */
		return cmpstr_ls_strict(s1, s2); 

	return (get_snum(s1[i]) - get_snum(s2[i]));
}

/**
 * cmpstr_ls_strict - compare two strings for ls
 * @s1: first string
 * @s2: second string
 * Return: 0 for equivalent strings, the difference between the first characters which differ for nonequivalent strings
 */
int cmpstr_ls_strict(char *s1, const char *s2)
{
	int i;
	i = 0;

	while (s1[i]==s2[i] && s1[i] != '\0')
		i++;
	      
	if (s1[i] == s2[i]) /* str are equivalent */
		return (0); 

	return (get_snum_strict(s1[i]) - get_snum_strict(s2[i]));
}

/**
 * get_snum - get sort value for given char
 * @c: character to get sort value for
 *
 * Return: int from 1 to 92
 */
int get_snum(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 7);
	if (c >= 'a' && c <= 'z')
		return (2*c - 153);
	if (c >= 'A' && c <= 'Z')
		return (2*c - 89); /* same val as lowercase of char */
	else
		return get_nonalphn_snum(c);
}

/**
 * get_snum_strict - get sort value for given char
 * @c: character to get sort value for
 *
 * Return: int from 1 to 92
 */
int get_snum_strict(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 7);
	if (c >= 'a' && c <= 'z')
		return (2*c - 153);
	if (c >= 'A' && c <= 'Z')
		return (2*c - 88);
	else
		return get_nonalphn_snum(c);
}

/**
 * get_nonalphn_snum - get sort value for given char
 * @c: character to get sort value for
 *
 * Return: int from 1 to 92; -1 if snum could not be id'd
 */
int get_nonalphn_snum(char c)
{
	int i;
	char *chars;

	/* might be good to init this elsewhere
	   to avoid reinitializing every time?
	*/
	chars = "`^~<=>| _,;:!?'\"()[]{}@$*\\&#%+";
	for (i = 0; i < 30; i++)
	{
		if (c == chars[i])
			return (i + 1);
	}
	return (-1);
}
