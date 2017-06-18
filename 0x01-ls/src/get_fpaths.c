#include "hls-components.h"

/* create an array of strings, but only for requested file types (non-hidden, all except implicit, or all) */

/**
 * get_fpaths - store the paths of files to be represented by hls in @fpaths
 * @fpaths_dp: ptr to fpaths ptr (ptr to linked list)
 * @dstrm: ptr to stream of directory to be represented by hls
 * @ftparams: int code specifying whether hls call should represent hidden files
 *     0    don't list hidden files in output
 *     1    don't list implicit hidden files in output
 *     2    do list hidden files in output
 *
 * Return: 0 for success, 1 for invalid fpaths
 */
int get_fpaths(List **fpaths_dp, DIR *dstrm, int ftparams)
{
	struct dirent *ent;

	if (*fpaths_dp != NULL)
		return (1);

	while ((ent = readdir(dstrm)) != NULL)
	{
		printf("\nfor %s:\n", ent->d_name);
		if (ent->d_name[0] == '.')
		{
			switch(ftparams)
			{
			case 0:
				continue;
			case 1:
				if (ent->d_name[1] == ('.'||'\0'))
						continue;
				else
					break;
			case 2:
				break;
		        /* TODO: could get rid of case 2 or */
                        /* add default/error case for non 0-2 code */
			}
		}
		printf("DEBUG: running alpha_insert\n");
		alpha_insert_in_list(fpaths_dp, ent->d_name);
	}
	return (0);
}
