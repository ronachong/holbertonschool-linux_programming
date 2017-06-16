#include <stdio.h>
#include "hls-components.h"
#include "list.h"

 /* implement default behavior when no farg passed */
 /* calculate return when multiple calls to ls are made */

/**
 * main - executes hls with file arguments from command line
 * @argc: number of command line arguments
 * @argv: array of string arguments from command line
 * Return: same as ls returns -
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int main(int argc, char **argv)
{
	int i;
	int fargc;
	List *fargs;

	/* create linked list of fargs */
	fargs = NULL;

	for (fargc = 0, i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		       {
			       fargc++;
			       if (add_node(&fargs, argv[i]) == 1)
			       {
				       printf("Error allocating space\n");
				       return (2);
			       }
		       }
	}
	print_list(fargs);
	printf("fargc is %i\n", fargc);


	/* if (fargc == 0) */
	/* 	return hls("N/A"); /\* change to cwd *\/ */
	/* if (fargc == 1) */
	/* 	return hls(argv[1]); */
	/* /\* probably have to sort dir paths before lsing *\/ */
	/* for (i = 1; i < fargc; i++) */
	/* { */
	/* 	if (i > 1) */
	/* 		putchar('\n'); */
	/* 	printf("%s:\n", argv[i]); */
	/* 	hls(argv[i]); */
	/* } */
	/* /\* compute return val *\/ */
	return (0);
}
