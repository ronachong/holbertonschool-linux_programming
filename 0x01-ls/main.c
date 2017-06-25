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
	int retnw;
	hls_opxns_t *opxns;
	int fargc;
	List *fargs;
	List *farg;

	/* printf("DB: main\n"); */

	/* parse argv for opxns, fargs, and fargc */
	opxns = NULL;
	fargs = NULL;
	fargc = 0;

	ret = parse_argv(&opxns, &fargs, &fargc, argc, argv);
	if (ret != 0)
	{
		free(opxns);
		return (ret);
	}

	/* printf("\nDEBUG opxns:\nftparams: %i\nfinfo : %i\npformat: %i\n\n", */
	/*        opxns->ftparams, opxns->finfo, opxns->pformat); */

	if (fargc == 0)
		ret = (hls(".", opxns));
	else if (fargc == 1)
		ret = (hls(fargs->str, opxns));
	else
	{
		for (i = 0, farg = fargs, ret = 0; i < fargc; i++, farg = farg->next)
		{
			if (i > 0)
				putchar('\n');
			printf("%s:\n", farg->str);
			retnw = hls(farg->str, opxns);
			ret = (retnw > ret) ? retnw:ret;
		}
	}
	/* TODO: free opxns, fargs.. does it matter if this is all the way back 
	   in main?
	 */
	free(opxns);
	free_list(fargs);

	return (ret);
}


/**
 * parse_argv - parse argv for options, file args, and file arg count
 * @opxns_dp: pointer to opxns pointer (opxns represents parameters for hls
 * call(s))
 * @fargs_dp: pointer to fargs pointer (fargs represents file arguments from
 * cmd line)
 * @fargc_p: pointer to fargc/count of file arguments from cmd line
 * @argc: count of all args from cmd line
 * @argv: string array of args from cmd line
 *
 * Return:
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int parse_argv(hls_opxns_t **opxns_dp, List **fargs_dp, int *fargc_p, int argc, char **argv)
{
	int i;
	int ret;

	/* printf("DB: - parse_argv\n"); */

	ret = initialize_opxns(opxns_dp);
	if (ret != 0)
		return ret;

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
			if (alpha_insert_in_list(fargs_dp, argv[i]) == 2)
				return (2);
		}
	}
	return (0);
}

/**
 * initialize_opxns - create struct representing params for hls call(s); set
 * values to default
 * @opxns_dp: pointer to hls_options_t pointer set to NULL
 *
 * Return: 0 for success, 1 for invalid opxns, 2 for malloc error
 */
int initialize_opxns(hls_opxns_t **opxns_dp)
{
	/* printf("DB: -- initialize_opxns\n"); */

	if (*opxns_dp != NULL)
	{
		printf("Programming error: *opxns_dp != NULL\n");
		return (1);
	}

	*opxns_dp = malloc(sizeof(struct hls_opxns));
	if (*opxns_dp == NULL)
	{
		perror("malloc");
		return (2);
	}

	(*opxns_dp)->fquery = 0;
	(*opxns_dp)->ftparams = 0;
	(*opxns_dp)->finfo = 0;
	(*opxns_dp)->forder = 1;
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

	/* printf("DB: -- get_opxns\n"); */

	for (i = 1; arg[i] != '\0'; i++)
	{
		switch (arg[i])
		{
		case 'A':
			if (opxns->ftparams != 2)
				opxns->ftparams = 1;
			break;
		case 'a':
			opxns->ftparams = 2;
			break;
		case 'S':
			opxns->forder = (opxns->forder > 0) ? 2:-2;
			if (opxns->finfo != 2)
				opxns->finfo = 1;
			break;
		case 'l':
			opxns->finfo = 2;
			opxns->pformat = 1;
			break;
		case '1':
			opxns->pformat = 1;
			break;
		case 'r':
			opxns->forder *= -1;
			break;
		default:
			printf("ls: invalid option -- '%c'\n", arg[i]);
			/* TODO: incorporate hls --help? */
			return (1);
		}	      
	}
	return (0);
}
