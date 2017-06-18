#include <stdio.h>
#include <stdlib.h>
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
	hls_opxns_t *opxns;
	int fargc;
	List *fargs;
	List *farg;

	/* parse argv for fargs, fargc, and opxns */
	opxns = NULL;
	fargs = NULL;

	if (initialize_opxns(&opxns) != 0)
		return (2);

	printf("opxns:\nftparams: %i\nfinfo : %i\npformat: %i\n",
	       opxns->ftparams, opxns->finfo, opxns->pformat);

	for (fargc = 0, i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-') /* arg is option(s) */
		{
			if (get_opxns(opxns, argv[i]) == 1)
				return (1);
		}
		else /* arg is file arg */
		{
			fargc++;
			if (alpha_insert_in_list(&fargs, argv[i]) == 1)
			{
				printf("Error allocating space\n");
				return (2);
			}
		}
	}

	printf("opxns:\nftparams: %i\nfinfo : %i\npformat: %i\n",
	       opxns->ftparams, opxns->finfo, opxns->pformat);

	if (fargc == 0)
		return hls("N/A"); /* TODO: change to cwd */
	if (fargc == 1)
		return hls(fargs->str);
	for (i = 0, farg = fargs; i < fargc; i++, farg = farg->next)
	{
		if (i > 0)
			putchar('\n');
		printf("%s:\n", farg->str);
		hls(farg->str);
	}
	/* TODO: compute return val */
	/* TODO: free fargs */
	return (0);
}


/**
 * intialize_opxns - create struct representing params for hls call(s); set
 * values to default
 * @opxns: pointer to hls_options_t pointer set to NULL
 * Return: 0 for success, 1 for invalid opxns, 2 for malloc error
 */
int initialize_opxns(hls_opxns_t **opxns_dp)
{
	if (*opxns_dp != NULL)
		return (1);

	*opxns_dp = malloc(sizeof(struct hls_opxns));
	if (*opxns_dp == NULL)
		return (2);

	printf("opxns_dp is %p\n", (void *) opxns_dp);
	(*opxns_dp)->ftparams = 0;
	(*opxns_dp)->finfo = 0;
	(*opxns_dp)->pformat = 0;

	return (0);
}

/**
 * get_opxns - parses arg for parameters for hls call(s)
 * @opxns: pointer to struct representing parameters for hls calls
 * @arg: string to parse for hls options
 * Return: 0 for success, 1 for error
 */
int get_opxns(hls_opxns_t *opxns, char *arg)
{
	int i;
	
	for (i = 1; arg[i] !='\0'; i++)
	{
		if (arg[i] == 'A' && opxns->ftparams != 2):
			opxns->ftparams = 1;
		else if (arg[i] == 2):
			opxns->ftparams = 2;
		else if (arg[i] == 'S' && opxns->finfo != 2):
			opxns->finfo = 1;
		else if (arg[i] == 'l'):
		{
			opxns->finfo = 2;
			opxns->pformat = 1;
		}
		else if (arg[i] = '1'):
			opxns->pformat = 1;
		else
		{
			printf("ls: invalid option -- '%c'\n", arg[i]);
			/* TODO: incorporate hls --help? */
			return (1);
		}
	}
	return (0);
}
