#include <stdio.h>
#include <stdlib.h>

char *strconcat(char *s1, char *s2);

int main()
{
  char *concat;
  char *fromlits;

  concat = strconcat("Holberton ", "School");
  fromlits = strconcat(" ,(.\n(   )\n `\"'\n", "filler string");
  printf("%s\n", concat);
  printf("%s\n", fromlits);
  free(concat);
  free(fromlits);
  return (0);
}
