#include "hls-components.h"

/* probably need to check return of open, read, and/or close? */

/**
 * hls - list the contents of a directory
 * @dpath: path of directory
 *
 * Return: same as ls returns -
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int hls(char *dpath, hls_opxns_t *opxns)
{
	DIR *dstrm;
	List *fpaths;
	finfo_t *finfo;

	fpaths = NULL; /* TODO: free linked list */
	finfo = NULL; /* TODO: free finfo list */
	dstrm = opendir(dpath);
	get_fpaths(&fpaths, dstrm, opxns->ftparams);
	closedir(dstrm);

	switch(opxns->finfo)
	{
	case 0:
		print_fnames(fpaths, opxns->pformat);
		break;
	case 1:
		get_finfo(&finfo, dpath, &fpaths);
		print_finfo(finfo, opxns->pformat);
		break;
	case 2:
		printf("\nDEBUG: output still to implement\n");
		break;
	}
	return (0);
}
