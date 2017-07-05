#include "_getline.h"

/**
 * _getline: reads one entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: line from file
 */
char *_getline(const int fd)
{
	size_t lsize;
	size_t bytes_rd;
	char buf[READ_SIZE];
	char *str;
	char *ret;

	str = malloc(READ_SIZE);

	do {
		/* TODO: handle read err */
		bytes_rd = read(fd, buf, READ_SIZE);
		lsize = update_str(&str, buf, bytes_rd);
	} while (str[lsize - 1] != '\0');

	ret = malloc(lsize);
	strncpy(ret, str, lsize);
	free(str);
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
size_t update_str(char **str_addr, char buf[], size_t bytes_rd)
{
	static size_t lsize = 0;
	static size_t wsize = 0;
	static size_t str_size = READ_SIZE;
	unsigned int i;

	if (bytes_rd == 0)
		return (lsize);

	for (i = 0; i < bytes_rd; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			break;
		}
	}

	wsize = lsize;
	lsize += i + 1;
	if (lsize > str_size)
		str_size = expand_str(str_addr, str_size, lsize);

	strncpy(*str_addr + wsize, buf, i + 1);
	return (lsize);
}


/**
 * expand_str: replaces the given array with another array twice the size
 * @str_addr: pointer to the array being replaced
 * @str_len: current number of bytes allocated to array
 * @lsize: "line size" - number of chars/bytes to copy to the new array
 *
 * Return:
 */
size_t expand_str(char **str_addr, size_t str_size, size_t lsize)
{
	char *nstr;

	str_size *= 2;
	nstr = malloc(str_size);
	strncpy(nstr, *str_addr, lsize); /* TODO: handle err */
	free(*str_addr);
	str_addr = &nstr;
	return (str_size);
}
