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
	char *err;
	int max;

	/* printf("DB: - hls\n"); */

	fpaths = NULL;
	finfo = NULL;
	vfinfo = NULL;
	err = NULL;
	max = 0;

	dstrm = opendir(dpath);
	if (dstrm == NULL)
	{
		switch (errno)
		{
			/* TODO: add cases for EBADF, EMFILE, ENFILE & ENOMEN?
			 */
		case EACCES:
			err = strconcat("hls: ", dpath);
			perror(err);
			closedir(dstrm);
			return (2);
		case ENOENT:
			err = strconcat("hls: cannot access ", dpath);
			perror(err);
			closedir(dstrm);
			return (2);
		case ENOTDIR:
			opxns->fquery = dpath;
			break;
		}
	}

	get_fpaths(&fpaths, dstrm, opxns->ftparams, opxns->fquery, opxns->forder);
	closedir(dstrm);

	switch (opxns->finfo)
	{
	case 0:
		print_fnames(fpaths, opxns->pformat);
		break;
	case 1:
		get_finfo(&finfo, dpath, &fpaths, opxns->forder);
		print_finfo(finfo, opxns->pformat);
		free_finfo(finfo);
		break;
	case 2:
		get_vfinfo(&vfinfo, dpath, &fpaths, opxns->forder, opxns->fquery, &max);
		print_vfinfo(vfinfo, max);
		free_vfinfo(vfinfo);
		break;
	}
        /* TODO: free fpaths linked list */
	free_list(fpaths);
	return (0);
}
