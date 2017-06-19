#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "list.h"
#include "str.h"

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
 *
 */
typedef struct hls_opxns
{
	int ftparams;
	int finfo;
	int pformat;
} hls_opxns_t;


/**
 * struct finfo_s - representation of file info (name and size)
 * @name: file name
 * @size: file size in bytes
 * @next: link to another finfo node in linked list
 */
typedef struct finfo_s
{
	char *name;
	int size;
	struct finfo_s *next;
} finfo_t;

/**
 * struct finfo_s - representation of file info (verbose)
 * @name: file name
 * @size: file size in bytes
 * @perm:
 * @smth:
 * @user:
 * @owner:
 * @date:
 * @next: link to another finfo node in linked list
 */
typedef struct vfinfo_s
{
	char *name;
	int size;
	char *perm;
	char *smth;
	char *user;
	char *owner;
	char *date;
	struct vfinfo_s *next;
} vfinfo_t;

int parse_argv(hls_opxns_t **opxns_dp, List **fargs_dp, int *fargc_p, int argc, char **argv);
int initialize_opxns(hls_opxns_t **opxns_dp);
int get_opxns(hls_opxns_t *opxns, char *arg);
int hls(char *dpath, hls_opxns_t *opxns);
int get_fpaths(List **fpaths_dp, DIR *dstrm, int ftparams);
int print_fnames(List *list, int pformat);
int get_finfo(finfo_t **finfo_dp, char *dpath, List **fpaths_dp);
int size_insert_in_finfo(finfo_t **finfo_dp, char *fname, int fsize);
int insert_fi_node(finfo_t *fi_node_prev, char *fname, int fsize);
int add_fi_node(finfo_t **finfo_dp, char *fname, int fsize);
int print_finfo(finfo_t *finfo, int pformat);
vfinfo_t **get_vfinfo(char **fpaths, char *opxns);
int print_vfinfo(vfinfo_t **vfinfo, char *opxns);

#endif
