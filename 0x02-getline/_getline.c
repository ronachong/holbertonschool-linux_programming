#include "_getline.h"
#include <malloc.h>

void test_read(const int fd)
{
	int i;
	char buf[READ_SIZE];
	for (i = 0; i < 5; i++)
	{
		read(fd, buf, READ_SIZE - 1);
		buf[READ_SIZE - 1] = '\0';
		printf("%i: in buffer: %s\n", i, buf);
	}
}

/**
 * _getline: reads one entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: line from file
 */
char *_getline(const int fd)
{
	static char *r_addr = NULL;
	static size_t strc = 0; /* chars written to curr str */
	static size_t bytes_rd = 0;
	static char buf[READ_SIZE];
	char *str;
	char *ret;

	int i = 0;
	str = malloc(READ_SIZE);

	do {
		if (r_addr == NULL)
		{
/* buffer never used or exhausted, overwrite */
			/* TODO: handle read err */
			bytes_rd = read(fd, buf, READ_SIZE);
			r_addr = buf;
		}

		strc = update_str(&str, r_addr, strc, bytes_rd);
		r_addr = NULL;
		i++;
	} while (str[strc - 1] != '\0' && i < 5);

	ret = malloc(strc);
	strncpy(ret, str, strc);
	free(str);

	r_addr = (strc != READ_SIZE) ? buf + strc : NULL;
	strc = 0;
	return (ret);
}

/**
 * update_str: copies appropriate chars from buffer to string
 * @str_addr: pointer to string
 * @buf: pointer to buffer containing chars
 * @bytes_rd: number of bytes/chars written to buffer
 *
 * Return: "line size" - updated count of chars assigned to string
 */
size_t update_str(char **str_addr, char *r_addr, size_t strc, size_t bytes_rd)
{
	static size_t str_size = READ_SIZE; /* size of str array */
	size_t new_strc;
	unsigned int i;

	if (bytes_rd == 0)
		return (strc);
       
	for (i = 0; i < bytes_rd; i++)
	{
		if (r_addr[i] == '\n')
		{
			r_addr[i] = '\0';
			i++;
			break;
		}
	}

 	new_strc = strc + i;
	if (new_strc > str_size)
		str_size = expand_str(str_addr, str_size, new_strc);

	strncpy(*str_addr + strc, r_addr, i);
	return (new_strc);
}


/**
 * expand_str: replaces the given array with another array twice the size
 * @str_addr: pointer to the array being replaced
 * @str_size: current number of bytes allocated to array
 * @strc: "line size" - number of chars/bytes to copy to the new array
 *
 * Return: updated size of array
 */
size_t expand_str(char **str_addr, size_t str_size, size_t strc)
{
	char *nstr;

	str_size *= 2;
	nstr = malloc(str_size);
	strncpy(nstr, *str_addr, strc); /* TODO: handle err */
	free(*str_addr);
	*str_addr = nstr;
	return (str_size);
}
