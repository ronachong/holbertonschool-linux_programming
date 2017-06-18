#include "hls-components.h"

/* create an array of strings, but only for requested file types (non-hidden, all except implicit, or all) */

/**
 * get_fpaths - get the paths of files to be represented by hls
 * @dstrm: ptr to stream of directory to be represented by hls
 * @ftparams: int code specifying whether hls call should represent hidden files
 *     0    don't list hidden files in output
 *     1    don't list implicit hidden files in output
 *     2    do list hidden files in output
 *
 * Return: 
 */
char **get_fpaths(DIR *dstrm, int ftparams)
{
	char **fpaths;
	struct dirent *ent;

	fpaths = NULL;
	ftparams = ftparams;

	while ((ent = readdir(dstrm)) != NULL)
		/* if filetype is hidden:
		   1. continue (skip) if ftparams is 0
		   2. continue (skip) if '.' and '..' and ftparams is 1:
		   3. execute like normal (add to char string) if ftparams is 2
		*/
		printf("%s\n", ent->d_name);
	return fpaths;
}
