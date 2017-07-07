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
	size_t c;
	char *str;
	char *ret;

	/* printf("\nnew call\n"); */

	str = malloc(READ_SIZE);

	do {
		if (r_addr == NULL)
		{ /* buffer fully parsed or never used, overwrite */
			/* TODO: handle read err */
			bytes_rd = read(fd, buf, READ_SIZE);
			/* printf("buf is %s\n", buf); */
			r_addr = buf;
		}

		c = c_to_copy(r_addr, bytes_rd);
		strc = update_str(&str, r_addr, strc, c);
		r_addr = NULL;		
	} while (str[strc - 1] != '\0');

	ret = malloc(strc);
	strncpy(ret, str, strc);
	free(str);

	/* ensure read of buf in next call if buf not fully parsed */
	if (READ_SIZE - c != 0)
	{		
		r_addr = buf + c;
		bytes_rd -= c;
		/* printf("r_addr for next call is %s\n", r_addr); */
	}
	strc = 0;
	return (ret);
}

/**
 * c_to_copy: finds the number of chars to copy from buf
 * @str_addr: pointer to string
 * @buf: pointer to buffer containing chars
 * @bytes_rd: number of bytes/chars written to buffer
 *
 * Return: updated count of chars assigned to string
 */
size_t c_to_copy(char *r_addr, size_t bytes_rd)
{
	unsigned int i;

	if (bytes_rd == 0)
		return (0);
       
	for (i = 0; i < bytes_rd; i++)
	{
		if (r_addr[i] == '\n')
		{
			r_addr[i] = '\0';
			i++;
			break;
		}
	}
	return (i);
}

/**
 * update_str: copies appropriate chars from buffer to string
 * @str_addr: pointer to string
 * @buf: pointer to buffer containing chars
 * @bytes_rd: number of bytes/chars written to buffer
 *
 * Return: updated count of chars assigned to string
 */
size_t update_str(char **str_addr, char *r_addr, size_t strc, size_t i)
{
	static size_t str_size = READ_SIZE; /* size of str array */
	size_t new_strc;

	if (i == 0)
		return (strc);

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