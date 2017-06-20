#include "hls-components.h"

/**
 * print_vfinfo - print names from sorted vfinfo list according to @pformat
 * @vfinfo: ptr to head in vfinfo linked list
 * @pformat: code representing whether to print one name per line or inline
 *
 * Return: 0 for success
 */
int print_vfinfo(vfinfo_t *vfinfo)
{
	vfinfo_t *vfi_node;

	printf("DB: in print_vfinfo\n");

	vfi_node = vfinfo;
	while (vfi_node != NULL)
	{
		printf("%s %i %s %s %i %s %s\n",
		       vfi_node->perm,
		       vfi_node->nlink,
		       vfi_node->uid,
		       vfi_node->gid,
		       vfi_node->size,
		       vfi_node->mtime,
		       vfi_node->name
			);
		vfi_node = vfi_node->next;

	}

	return (0);
}
