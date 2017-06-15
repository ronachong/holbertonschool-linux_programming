#include <stdio.h>
#include "ls-components.h"

/* probably need to check return of open, read, and/or close? */
int ls(char *dpath)
{
	DIR *dir;
	struct dirent *ent;

	printf("Inside ls: dpath is %s\n", dpath);
	dir = opendir(dpath);
	printf("Opened stream to dpath; ptr is %p\n", (void *) dir);
	while ((ent = readdir(dir)) != NULL)
		printf("%s\n", ent->d_name);
	closedir(dir);
	return (0);
}
