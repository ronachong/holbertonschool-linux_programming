#include "hls-components.h"

/**
 * print_vfinfo - print names from sorted vfinfo list according to @pformat
 * @vfinfo: ptr to head in vfinfo linked list
 * @pformat: code representing whether to print one name per line or inline
 *
 * Return: 0 for success
 */
int print_vfinfo(vfinfo_t *vfinfo, int max)
{
	vfinfo_t *vfi_node;
	char mtime[13];
	int i;
	int j;
	int size;
	int sdiff;
	int k;
	char *padding;

	/* printf("DB: -- print_vfinfo\n"); */

	j = 0;
	while (max > 9)
	{
		max /= 10;
		j++;
	}

	vfi_node = vfinfo;
	while (vfi_node != NULL)
	{
		for (size = vfi_node->size, k = 0;
		     size > 9;
		     k++)
			size /= 10;

		sdiff = j - k;
		if (sdiff > 0)
		{
			padding = malloc(sdiff + 1);
			for (i = 0; i < sdiff; i++)
				padding[i] = ' ';
			padding[sdiff] = '\0';
		}
		else
			padding = "";

		for (i = 0; i < 16; i++)
		{
			while (i < 4)
			{
				i++;
				continue;
			}
			mtime[i - 4] = (vfi_node->mtime)[i];
		}
		mtime[12] = '\0';

		printf("%s %i %s %s %s%i %s %s\n",
		       vfi_node->perm,
		       vfi_node->nlink,
		       vfi_node->uid,
		       vfi_node->gid,
		       padding,
		       vfi_node->size,
		       mtime,
		       vfi_node->name
			);
		vfi_node = vfi_node->next;
		if (sdiff > 0)
			free(padding);
	}

	return (0);
}
