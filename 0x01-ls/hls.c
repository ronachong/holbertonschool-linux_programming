#include "hls-components.h"

/* probably need to check return of open, read, and/or close? */

/**
 * hls - list the contents of a directory
 * @dpath: path of directory
 * @opxns: struct representing params for hls call
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
	vfinfo_t *vfinfo;

	fpaths = NULL;
	finfo = NULL;
	vfinfo = NULL;

	dstrm = opendir(dpath);
	get_fpaths(&fpaths, dstrm, opxns->ftparams);
	closedir(dstrm);

	switch (opxns->finfo)
	{
	case 0:
		print_fnames(fpaths, opxns->pformat);
		break;
	case 1:
		get_finfo(&finfo, dpath, &fpaths);
		print_finfo(finfo, opxns->pformat);
                /* TODO: free finfo list */
		break;
	case 2:
		get_vfinfo(&vfinfo, dpath, &fpaths);
		print_vfinfo(vfinfo);
		/* TODO: free vfinfo list */
		break;
	}

        /* TODO: free fpaths linked list */
	return (0);
}
