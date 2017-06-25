#include "str.h"
#include "hls-components.h"

char *strconcat(char *s1, char *s2)
{
	char *dest;
	int i;
	int j;

	if (cmpstr(s1, "") == 0)
	    return (s2);

	if (cmpstr(s2, "") == 0)
	    return (s1);

	dest = malloc(get_len(s1) + get_len(s2) - 1);

	/* if malloc fails, return NULL */
	if (dest == NULL)
		return NULL;

	for (i = 0; s1[i] != '\0'; i++)
		dest[i] = s1[i];

	for (j = 0; s2[j] != '\0'; j++, i++)
		dest[i] = s2[j];

	dest[i] = '\0';

	return (dest);
}

int get_len(char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; i++)
	{}
	return (i + 1);
}
