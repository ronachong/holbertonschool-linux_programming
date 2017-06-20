#include "hls-components.h"

/**
 * get_vfinfo - store verbose details about files in vfinfo linked list
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @dpath: path of directory containing files represented by vfinfo linked list
 * @fpaths_dp: ptr to ptr to head of linked list of files to stat
 *
 * Return: 0 for success
 */
int get_vfinfo(vfinfo_t **vfinfo_dp, char *dpath, List **fpaths_dp)
{
	List *path;
	struct stat stat;

	printf("in get_vfinfo\n");

	if (dpath[get_len(dpath) - 1] != '/')
		dpath = strconcat(dpath, "/");
	/* TODO: free allocated dpath? */

	for (path = *fpaths_dp; path != NULL; path = path->next)
	{
		/* query lstat for file size */
		lstat(strconcat(dpath, path->str), &stat);
		/* printf("DB: %s: size is %i\n", path->str, (int) stat.st_size); */
		size_insert_in_vfinfo(vfinfo_dp, path->str, stat);
	}
	return (0);
}


/**
 * size_insert_in_vfinfo - insert new node in vfinfo linked list by size of file
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @fname: file name to store in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int size_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	/* int i; */
	vfinfo_t *vfi_node;
	vfinfo_t *vfi_node_prev;

	printf("in size_insert_vfinfo\n");

	/* i = 0; */
	vfi_node = *vfinfo_dp;

	if (vfi_node == NULL)
		return (add_vfi_node(vfinfo_dp, fname, stat));

	if (vfi_node->size < stat.st_size)
	{
		add_vfi_node(vfinfo_dp, fname, stat);
		(*vfinfo_dp)->next = vfi_node;
		return (0);
	}

	while (vfi_node->size >= stat.st_size)
	{
		if (vfi_node->size == stat.st_size && cmpstr(fname, vfi_node->name) < 0)
			break;
		vfi_node_prev = vfi_node;
		if (vfi_node->next == NULL)
			break;
		vfi_node = vfi_node->next;
	}
	/* printf("inserting after %p\n", (void *)vfi_node_prev); */
	insert_vfi_node(vfi_node_prev, fname, stat);

	return (0);
}

/**
 * insert_vfi_node - insert a new vfinfo node after @vfi_node_prev
 * @vfi_node_prev: ptr to the node after which new node will be inserted
 * @fname: file name to be stored in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int insert_vfi_node(vfinfo_t *vfi_node_prev, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node_new;

	printf("in insert_vfinfo\n");

	vfi_node_new = malloc(sizeof(vfinfo_t));
	if (vfi_node_new == NULL)
		return (2);

	/* TOCHECK: is using the og values ok for ptrs, or should i use copy_str? */
	vfi_node_new->name = fname; /* TODO: fix copy_str? */
	vfi_node_new->size = stat.st_size;
	vfi_node_new->perm = "tbi";
	vfi_node_new->nlink = stat.st_nlink;
	vfi_node_new->uid = "tbi"; /* stat.st_uid; */
	vfi_node_new->gid = "tbi"; /* stat.st_gid; */
	vfi_node_new->mtime = "tbi"; /* stat.st_mtime; */
	vfi_node_new->next = vfi_node_prev->next;


	vfi_node_prev->next = vfi_node_new;
	return (0);
}

/**
 * add_vfi_node - add a vfinfo node as head to linked vfinfo list
 * @vfinfo_dp: pointer to ptr to head of linked vfinfo list
 * @fname: file name to store in vfinfo node
 * @fsize: file size to store in vfinfo node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int add_vfi_node(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;

	printf("in add_vfi_node\n");

	vfi_node = malloc(sizeof(vfinfo_t));
	if (vfi_node == NULL)
		return (2);

	/* TOCHECK: is using the og values ok for ptrs, or should i use copy_str? */
	vfi_node->name = copy_string(fname); /* TODO: fix copy_str? */
	vfi_node->size = stat.st_size;
	vfi_node->perm = "tbi";
	vfi_node->nlink = stat.st_nlink;
	vfi_node->uid = "tbi"; /* stat.st_uid; */
	vfi_node->gid = "tbi"; /* stat.st_gid; */
	vfi_node->mtime = "tbi"; /* stat.st_mtime; */
	vfi_node->next = *vfinfo_dp;

	*vfinfo_dp = vfi_node;
	return (0);
}
