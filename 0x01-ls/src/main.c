#include <stdio.h>
#include "ls-components.h"

/**
 * main - executes hls with file arguments from command line
 * @argc: number of command line arguments
 * @argv: array of string arguments from command line
 * Return: based on ls -
 *     0      if OK,
 *     1      if minor problems (e.g., cannot access subdirectory),
 *     2      if serious trouble (e.g., cannot access command-line argument).
 */
int main(int argc, char **argv)
{
	int i;

	if (argc == 1)
		return hls("N/A"); /* change to cwd */
	if (argc == 2)
		return hls(argv[1]);
	/* probably have to sort dir paths before lsing */
	for (i = 1; i < argc; i++)
	{
		if (i > 1)
			putchar('\n');
		printf("%s:\n", argv[i]);
		hls(argv[i]);
	}
	/* compute return val */
	return (0);
}
