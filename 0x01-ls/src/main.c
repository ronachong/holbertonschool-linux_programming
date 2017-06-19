#include "hls-components.h"

 /* implement default behavior when no farg passed */
 /* calculate return when multiple calls to ls are made */

/**
 * main - executes hls with file arguments from command line
 * @argc: number of command line arguments
 * @argv: array of string arguments from command line
 *
 * Return: same as ls returns -
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int main(int argc, char **argv)
{
	int i;
	int ret;
	hls_opxns_t *opxns;
	int fargc;
	List *fargs;
	List *farg;

	/* parse argv for opxns, fargs, and fargc */
	opxns = NULL;
	fargs = NULL;
	fargc = 0;
	if ((ret = parse_argv(&opxns, &fargs, &fargc, argc, argv)) != 0)
		return (ret);

	/* printf("\nDEBUG opxns:\nftparams: %i\nfinfo : %i\npformat: %i\n\n", */
	/*        opxns->ftparams, opxns->finfo, opxns->pformat); */

	if (fargc == 0)
		return hls(".", opxns);
	if (fargc == 1)
		return hls(fargs->str, opxns);
	for (i = 0, farg = fargs; i < fargc; i++, farg = farg->next)
	{
		if (i > 0)
			putchar('\n');
		printf("%s:\n", farg->str);
		hls(farg->str, opxns);
	}
	/* TODO: compute return val */
	/* TODO: free fargs */
	return (0);
}


/**
 * parse_argv - parse argv for options, file args, and file arg count
 * @opxns_dp - pointer to opxns pointer (opxns represents parameters for hls
 * call(s))
 * @fargs_dp - pointer to fargs pointer (fargs represents file arguments from
 * cmd line)
 * @fargc_p - pointer to fargc/count of file arguments from cmd line
 * @argc - count of all args from cmd line
 * @argv - string array of args from cmd line
 *
 * Return:
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int parse_argv(hls_opxns_t **opxns_dp, List **fargs_dp, int *fargc_p,
	       int argc, char **argv)
{
	int i;

	if (initialize_opxns(opxns_dp) != 0)
		return (2);

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-') /* arg is option(s) */
		{
			if (get_opxns(*opxns_dp, argv[i]) == 1)
				return (1);
		}
		else /* arg is file arg */
		{
			(*fargc_p)++;
			if (alpha_insert_in_list(fargs_dp, argv[i]) == 1)
			{
				printf("Error allocating space\n");
				return (2);
			}
		}
	}
	return (0);
}

/**
 * intialize_opxns - create struct representing params for hls call(s); set
 * values to default
 * @opxns: pointer to hls_options_t pointer set to NULL
 *
 * Return: 0 for success, 1 for invalid opxns, 2 for malloc error
 */
int initialize_opxns(hls_opxns_t **opxns_dp)
{
	if (*opxns_dp != NULL)
		return (1);

	*opxns_dp = malloc(sizeof(struct hls_opxns));
	if (*opxns_dp == NULL)
		return (2);

	(*opxns_dp)->ftparams = 0;
	(*opxns_dp)->finfo = 0;
	(*opxns_dp)->pformat = 0;

	return (0);
}

/**
 * get_opxns - parses arg for parameters for hls call(s)
 * @opxns: pointer to struct representing parameters for hls calls
 * @arg: string to parse for hls options
 *
 * Return: 0 for success, 1 for error
 */
int get_opxns(hls_opxns_t *opxns, char *arg)
{
	int i;

	for (i = 1; arg[i] != '\0'; i++)
	{
		if (arg[i] == 'A' && opxns->ftparams != 2)
			opxns->ftparams = 1;
		else if (arg[i] == 'a')
			opxns->ftparams = 2;
		else if (arg[i] == 'S' && opxns->finfo != 2)
			opxns->finfo = 1;
		else if (arg[i] == 'l')
		{
			opxns->finfo = 2;
			opxns->pformat = 1;
		}
		else if (arg[i] == '1')
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
