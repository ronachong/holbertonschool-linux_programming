#include "hls-components.h"

/* probably need to check return of open, read, and/or close? */

/**
 * hls - list the contents of a directory
 * @dpath: path of directory
 * Return: same as ls returns -
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int hls(char *dpath)
{
	DIR *dstrm;

	printf("Inside ls: dpath is %s\n", dpath);
	dstrm = opendir(dpath);
	printf("Opened stream to dpath; ptr is %p\n", (void *) dstrm);

	/* get_fpaths(dstrm, opxns); */
	

	closedir(dstrm);
	return (0);
}
