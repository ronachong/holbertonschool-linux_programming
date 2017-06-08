#include <stdio.h>
#include <stdlib.h>

char *strconcat(char *s1, char *s2)
{
  char *s3;
  int i;
  int j;

  s3 = malloc(sizeof(s1) + sizeof(s2));
	    
  /* if malloc fails, return NULL */
  if (s3 == NULL)
    return NULL;

  for (i = 0; s1[i] != '\0'; i++)
    s3[i] = s1[i];

  for (j = 0; s2[j] != '\0'; j++, i++)
    s3[i] = s2[j];

  return s3;
}
