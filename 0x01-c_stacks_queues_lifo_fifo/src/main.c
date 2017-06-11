#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  argv++;

  if (argc != 2)
    {
      printf("USAGE: monty file\n");
      return (EXIT_FAILURE);
    }
  printf("ran to completion\n");
  return (EXIT_SUCCESS);
}
