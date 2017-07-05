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
	char *line;

	fd = open("main.c", 0);
	line = _getline(fd);
	printf("%s\n", line);
	free(line);

	/* while ((line = _getline(fd))) */
	/* { */
	/* 	printf("%s\n", line); */
	/* 	free(line); */
	/* } */
	close(fd);
	return (0);
}
