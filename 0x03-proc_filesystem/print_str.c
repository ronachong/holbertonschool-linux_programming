#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR "String 1"

void cpy_str(const char *str, char *dst);

int main(void)
{
	char *str;

	str = malloc(strlen(STR) + 1); /* belongs to heap */
	cpy_str(STR, str);

	while (1)
	{
		printf("%s\n", str);
		sleep(1);
	}

	free(str);
	return (0);
}

/** cpy_str - copies string literal to dst
 */
void cpy_str(const char *str, char *dst)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		dst[i] = str[i];

	dst[i] = '\0';
}
