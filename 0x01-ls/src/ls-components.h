#ifndef HEADER_FILE
#define HEADER_FILE
#include <dirent.h>

typedef struct fname_s
{
	char *name;
	struct fname_s *next;
} fname_t;

typedef struct finfo_s
{
	char *name;
	int *size;
	struct finfo_s *next;
} finfo_t;

typedef struct vfinfo_s
{
	char *name;
	int *size;
	char *perm;
	char *smth;
	char *user;
	char *owner;
	char *date;
	struct vfinfo_s *next;
} vfinfo_t;

int ls(char *dpath);
char **get_fpaths(DIR *dstrm, char *opxns);
fname_t **get_fnames(char **fpaths, char *opxns);
int print_fnames(fname_t **fnames, char *opxns);
finfo_t **get_finfo(char **fpaths, char *opxns);
int print_finfo(finfo_t **finfo, char *opxns);
vfinfo_t **get_vfinfo(char **fpaths, char *opxns);
int print_vfinfo(vfinfo_t **vfinfo, char *opxns);

#endif
