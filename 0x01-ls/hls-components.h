#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
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
 * @forder: order in which to output file names/details
 *     1    alphabetically
 *    -1    reverse alphabetically
 *     2    by size desc, then alphabetically
 *    -2    by size asc, then alphabetically
 * @pformat: printing format for output
 *     0    use new line as separator between file names or info
 *     1    use space as separator between file names or info
 *
 */
typedef struct hls_opxns
{
	int ftparams;
	int finfo;
	int forder;
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
 * @perm: file permissions
 * @nlink: number of links to file
 * @uid: owner user
 * @gid: owner group
 * @mtime: date modified
 * @next: link to another finfo node in linked list
 */
typedef struct vfinfo_s
{
	char *name;
	int size;
	char *perm;
	int nlink;
	char *uid;
	char *gid;
	char *mtime;
	struct vfinfo_s *next;
} vfinfo_t;

int parse_argv(hls_opxns_t **opxns_dp, List **fargs_dp, int *fargc_p, int argc, char **argv);
int initialize_opxns(hls_opxns_t **opxns_dp);
int get_opxns(hls_opxns_t *opxns, char *arg);
int hls(char *dpath, hls_opxns_t *opxns);
int get_fpaths(List **fpaths_dp, DIR *dstrm, int ftparams);
void print_fnames(List *list, int pformat);
int get_finfo(finfo_t **finfo_dp, char *dpath, List **fpaths_dp);
int size_insert_in_finfo(finfo_t **finfo_dp, char *fname, int fsize);
int insert_fi_node(finfo_t *fi_node_prev, char *fname, int fsize);
int add_fi_node(finfo_t **finfo_dp, char *fname, int fsize);
int print_finfo(finfo_t *finfo, int pformat);
int free_finfo(finfo_t *finfo);
int get_vfinfo(vfinfo_t **vfinfo_dp, char *dpath, List **fpaths_dp, int forder);
int alpha_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat);
int size_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat);
int insert_vfi_node(vfinfo_t *vfi_node_prev, char *fname, struct stat stat);
int add_vfi_node(vfinfo_t **vfinfo_dp, char *fname, struct stat stat);
vfinfo_t *get_vfi_node(char *fname, struct stat stat);
char *get_pstrv(int mode);
int print_vfinfo(vfinfo_t *vfinfo);
int free_vfinfo(vfinfo_t *vfinfo);

#endif
