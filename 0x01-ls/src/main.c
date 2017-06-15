#include <stdio.h>
#include "ls-components.h"

int main(int argc, char **argv)
{
	int i;

	if (argc == 1)
		return ls(/* cwd path */);
	if (argc == 2)
		return ls(argv[1]); /* to qualify path? */
	for (i = 1; i < argc; i++)
	{
		printf("%s:\n", argv[i]);
		ls(argv[i]); /* need to qualify path? */
	}
	/* compute return val */
	return (0);
}
