#ifndef HEADER_FILE
#define HEADER_FILE
#include <dirent.h>
#include <sys/types.h>


/**
 * struct hls_opxns - representation of parameters for hls call
 * @ftparams: file types to include in output
 *     0    don't list hidden files in output
 *     1    don't list implicit hidden files in output
 *     2    do list hidden files in output
 * @finfo: file info to retrieve
 *     0    name only
 *     1    name and size
 *     2    name, size, and other details
 * @pformat: printing format for output
 *     0    use new line as separator between file names or info
 *     1    use space as separator between file names or info
 * Description: 
 *
 */
typedef struct hls_opxns
{
	int *ftparams;
	int *finfo;
	int *pformat;
} hls_opxns_t;


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

int initialize_opxns(hls_opxns_t **opxns);
int get_opxns(hls_opxns_t **opxns, char *arg);
int hls(char *dpath);
char **get_fpaths(DIR *dstrm, char *opxns);
fname_t **get_fnames(char **fpaths, char *opxns);
int print_fnames(fname_t **fnames, char *opxns);
finfo_t **get_finfo(char **fpaths, char *opxns);
int print_finfo(finfo_t **finfo, char *opxns);
vfinfo_t **get_vfinfo(char **fpaths, char *opxns);
int print_vfinfo(vfinfo_t **vfinfo, char *opxns);

#endif
