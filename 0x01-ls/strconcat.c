#include "str.h"
#include "hls-components.h"

char *strconcat(char *s1, char *s2)
{
	char *s3;
	int i;
	int j;

	if (cmpstr(s1, "") == 0)
	    return (s2);

	if (cmpstr(s2, "") == 0)
	    return (s1);

	s3 = malloc(get_len(s1) + get_len(s2));

	/* if malloc fails, return NULL */
	if (s3 == NULL)
		return NULL;

	for (i = 0; s1[i] != '\0'; i++)
		s3[i] = s1[i];

	for (j = 0; s2[j] != '\0'; j++, i++)
		s3[i] = s2[j];

	s3[i] = '\0';

	return (s3);
}

int get_len(char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; i++)
	{}
	return (i);
}
