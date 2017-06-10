#include "100-op.h"
#include <stdio.h>
#include <stdlib.h>

char *basefunc(char *fruitstr, char *s2)
{
  /* char *substr; */
  /* char *substr2; */
  /* char *fullstr; */

  /* substr = strconcat(fruitstr, s2); */
  /* substr2 = strconcat(substr, "\n"); */
  /* fullstr = strconcat(substr2, fruitstr); */

  /* free(substr); */
  /* free(substr2); */
  /* return fullstr; */

  char *str;
  char *tmp;

  tmp = strconcat(fruitstr, s2);
  str = strconcat(tmp, "\n");
  free(tmp);
  tmp = str;
  str = strconcat(tmp, fruitstr);
  free(tmp);

  return str;
}
