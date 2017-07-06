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
	/* int i; */
	char *line;

	fd = open("main.c", 0);

	/* TEST 1 */
	/* for (i = 0; i < 5; i++) */
	/* 	test_read(fd); */

	/* TEST 2 */
	/* line = _getline(fd); */
	/* printf("%s\n", line); */
	/* free(line); */

	/* TEST 3 */
	while ((line = _getline(fd)))
	{
		printf("%s\n", line);
		free(line);
	}

	close(fd);
	return (0);
}
