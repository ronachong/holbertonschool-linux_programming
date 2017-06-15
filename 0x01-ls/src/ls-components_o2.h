#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct fname_s
{
	char *name;
	fname_s *next;
} fname_t;

typedef struct finfo_s
{
	char *name;
	int *size;
	finfo_s *next;
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
	vfinfo_s *next;
} vfinfo_t;

int ls(char *dpath);
char **fpaths get_fpaths(DIR *dstrm, char *opxns);
fname_t **fnames get_fnames(char **fpaths, char *opxns);
int print_fnames(fnames_t **fnames, char *opxns);
finfo_t **finfo get_finfo(char **fpaths, char *opxns);
int print_finfo(finfo_t **finfo, char *opxns);
vfinfo_t **vfinfo get_vfinfo(char **fpaths, char *opxns);
int print_vfinfo(vfinfo_t **vfinfo, char *opxns);

#endif
