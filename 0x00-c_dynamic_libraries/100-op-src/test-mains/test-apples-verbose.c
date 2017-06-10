#include <stdio.h>
#include <stdlib.h>
char *strconcat(char *s1, char *s2);
char *basefunc(char *fruitstr, char *s2);

char *apples(char *s)
{
  /* char *fruitstr; */

  /* fruitstr = malloc(sizeof(" ,(.\n(   )\n `\"'\n")); */
  /* for (i = */ 
  return basefunc(" ,(.\n(   )\n `\"'\n", s);
}
 

char *basefunc(char *fruitstr, char *s2)
{ 
  char *substr;
  char *fromlits;
  char *substr2;
  char *fullstr;

  substr = strconcat(fruitstr, s2);
  fromlits = strconcat(" ,(.\n(   )\n `\"'\n", "filler string");
  substr2 = strconcat(substr, "\n");
  fullstr = strconcat(substr, fruitstr);

  printf("%s", fruitstr);
  printf("that was fruitstr\n\n");
  printf("%s", s2);
  printf("that was s2\n\n");
  printf("%s", fromlits);
  printf("that was fromlits\n\n");
  printf("%s", substr);
  printf("that was substr\n\n");
  printf("%s", substr2);
  printf("that was substr2\n\n");
  printf("%s", fullstr);
  printf("that was fullstr\n\n");

  free(substr);
  free(substr2);
  return fullstr;

  /* char *substr; */

  /* substr = strconcat(fruitstr, s2); */
  /* printf("%s", substr); */
  /* substr = strconcat(substr, "\n"); */
  /* printf("%s", substr); */
  /* substr = strconcat(substr, fruitstr); */

  return substr;
}

int main(void)
{
  /* printf("%s", strconcat(" ,(.\n(   )\n `\"'\n", "filler string")); */
  apples("filler string");
  return (0);
}
