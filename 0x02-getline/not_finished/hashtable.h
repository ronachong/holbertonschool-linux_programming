#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
 * @key: fd key. The key is unique in the HashTable
 * @buf: The buf containing read but unparsed content for a fd.
 * @sz: size of buf
 * @next: A pointer to the next node of the List
 */
typedef struct List
{
	const int fd;
	char *buf;
	int sz;
	struct List *next;
} List;

/*
 * @size : The size of the array
 * @array : An array of size @size
 * Each cell of this array is a pointer to the first node of a linked list,
 * because we want our HashTable to use a Chaining collision handling
 */
typedef struct HashTable
{
  unsigned int size;
  List **array;
} HashTable;

/*
 * @key : The key to hash
 * @size : The size of the hashtable
 * @return : An integer N like 0 <= N < @size
 * This integer represents the index of @key in an array of size @size
 */
unsigned int hash(const char *key, unsigned int size);

#endif
