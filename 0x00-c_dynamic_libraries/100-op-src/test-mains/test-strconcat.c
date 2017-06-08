#include <stdio.h>
#include <stdlib.h>

char *strconcat(char *s1, char *s2);

int main()
{
  char *concat;

  concat = strconcat("Holberton ", "School");
  printf("%s\n", concat);
  free(concat);
  return (0);
}
