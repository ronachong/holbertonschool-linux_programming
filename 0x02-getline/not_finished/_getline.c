#include "_getline.h"
#include "hash_tables/ht_create.c"
#include "hash_tables/ht_get.c"
#include "hash_tables/ht_put.c"
#include "hash_tables/ht_free.c"

/**
 * _getline - reads one entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: line from file
 */
char *_getline(const int fd)
{
	static HashTable *ht = ht_create(HT_START_SIZE);
	static HashTable *ht_tmp;
	static size_t ht_size = HT_START_SIZE;
	static size_t ht_elmts = 0;


	static int fd_prev;
	static int ht
	static char *r_addr;
	static size_t strc; /* chars written to curr str */
	static size_t bytes_rd;
	static char buf[READ_SIZE];
	size_t c;
	char *str;
	char *ret;

	if (fd != fd_prev)
	{
		(update ht fxns to have a size field)
		/* copy buf */
		
		/* how will bytes_rd be set appropriately? */

		/* save buf to hashtable */
		if (ht_elmts + 1 > ht_size)
		{
			ht_tmp = ht;
			ht_free(ht_tmp);
			ht = ht_create(ht_size *= 2);
			ht_put(ht, fd,);
		}
	}


	if (fd != fd_prev || fd == -1)
	{	
		r_addr = NULL;
		strc = 0;
		bytes_rd = 0;

		if (fd == -1)
		{
			ht_tmp = ht;
			ht_free(ht_tmp);
			ht = ht_create(HT_START_SIZE);
			ht_size = HT_START_SIZE;
			return (NULL);
		}
	}

	str = malloc(READ_SIZE);

	do {
		if (r_addr == NULL)
		{ /* overwrite if buffer fully parsed or never used*/
			/* TODO: handle read err */
			bytes_rd = read(fd, buf, READ_SIZE);
			r_addr = buf;
		}

		c = c_to_copy(r_addr, bytes_rd);
		if (c == 0)
		{
			free(str);
			return (NULL);
		}
		strc = update_str(&str, r_addr, strc, c);

		if (c == bytes_rd) /* buffer fully parsed */
			r_addr = NULL;

	} while (str[strc - 1] != '\0');

	ret = malloc(strc);
	strncpy(ret, str, strc);
	free(str);
	strc = 0;
	fd_prev = fd;

	if (r_addr != NULL)
	{
		r_addr = r_addr + c;
		bytes_rd -= c;
	}

	return (ret);
}

/**
 * c_to_copy - finds the number of chars to copy from buffer
 * @r_addr: "read address" - pointer to buffer containing chars
 * @bytes_rd: number of bytes/chars written to buffer
 *
 * Return: number of chars to copy from buffer
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
 * update_str - copies appropriate chars from buffer to string
 * @str_addr: pointer to string
 * @r_addr: "read address" - pointer to buffer
 * @strc: number of chars written to string so far
 * @i: number of chars to write to string from buffer
 *
 * Return: updated count of chars assigned to string
 */
size_t update_str(char **str_addr, char *r_addr, size_t strc, size_t i)
{
	static size_t str_size = READ_SIZE; /* size of str array */
	size_t new_strc;

	if (i == 0)
		return (strc);

	if (strc == 0)
		str_size = READ_SIZE;

	new_strc = strc + i;

	if (new_strc > str_size)
		str_size = expand_str(str_addr, str_size, new_strc);

	strncpy(*str_addr + strc, r_addr, i);
	return (new_strc);
}


/**
 * expand_str - replaces the given array with another array twice the size
 * @str_addr: pointer to the array being replaced
 * @str_size: current number of bytes allocated to array
 * @strc: number of chars/bytes to copy to the new array
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
