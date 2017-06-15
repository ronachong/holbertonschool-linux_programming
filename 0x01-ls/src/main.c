#include <stdio.h>
#include "ls-components.h"

int main(int argc, char **argv)
{
	int i;

	if (argc == 1)
		return ls("N/A"); /* change to cwd */
	if (argc == 2)
		return ls(argv[1]);
	/* probably have to sort dir paths before lsing */
	for (i = 1; i < argc; i++)
	{
		if (i > 1)
			putchar('\n');
		printf("%s:\n", argv[i]);
		ls(argv[i]);
	}
	/* compute return val */
	return (0);
}
