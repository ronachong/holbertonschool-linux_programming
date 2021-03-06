#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open("main.c", 0);

	/* TEST 2 */
 	/* line = _getline(fd); */
	/* printf("%s\n", line); */
	/* free(line); */

	/* TEST 3 */
	while ((line = _getline(fd)) && i < 50)
	{
		printf("%s\n", line);
		free(line);
		i++;
	}

	close(fd);
	return (0);
}
