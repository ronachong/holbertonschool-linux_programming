#include "hls-components.h"

/* create an array of strings, but only for requested file types (non-hidden, all except implicit, or all) */

/**
 * get_fpaths - get the paths of files to be represented by hls
 * @dstrm: 
 * @opxns: 
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
		   1. continue (skip) if opxns->
		   2. continue (skip) if '.' and '..' and -A in opxns:
		   3. execute like normal (add to char string) if -a in options
		*/
		printf("%s\n", ent->d_name);
	return fpaths;
}
