#include "hls-components.h"

/**
 * print_finfo - print names from sorted finfo list according to @pformat
 * @finfo: ptr to head in finfo linked list
 * @pformat: code representing whether to print one name per line or inline
 *
 * Return: 0 for success
 */
int print_finfo(finfo_t *finfo, int pformat)
{
	char *sep;
	finfo_t *fi_node;

	if (pformat == 1)
		sep = "\n";
	else /* pformat should be 0 */
		sep = "  ";

	for (fi_node = finfo; fi_node->next != NULL; fi_node = fi_node->next)
		printf("%s%s", fi_node->name, sep);
	printf("%s\n", fi_node->name);

	return (0);
}
