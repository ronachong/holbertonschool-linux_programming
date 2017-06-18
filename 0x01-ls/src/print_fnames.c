#include "hls-components.h"

/**
 * print_fnames -
 *
 * Return:
 */
int print_fnames(List *fnames, int pformat)
{
	char *sep;
	List *name;

	if (pformat == 1)
		sep = "\n";
	else /* pformat should be 0 */
		sep = "  ";
	
	for (name = fnames; name->next != NULL; name = name->next)
		printf("%s%s", name->str, sep);
	printf("%s\n", name->str);

	return (0);
}
