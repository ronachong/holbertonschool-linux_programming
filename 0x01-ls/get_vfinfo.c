#include "hls-components.h"

/**
 * get_vfinfo - store verbose details about files in vfinfo linked list
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @dpath: path of directory containing files represented by vfinfo linked list
 * @fpaths_dp: ptr to ptr to head of linked list of files to stat
 *
 * Return: 0 for success
 */
int get_vfinfo(vfinfo_t **vfinfo_dp, char *dpath, List **fpaths_dp,
	       int forder, char *fquery, int *max)
{
	List *path;
	char *stpath;
	struct stat stat;

	/* printf("DB: -- get_vfinfo\n"); */
	/* printf("forder is %i\n", forder); */

	if (fquery != NULL)
		dpath = "";

 	else if (dpath[get_len(dpath) - 1] != '/')
		dpath = strconcat(dpath, "/");

	for (path = *fpaths_dp; path != NULL; path = path->next)
	{
		stpath = strconcat(dpath, path->str);
		lstat(stpath, &stat);
		free(stpath);
		if (stat.st_size > *max)
			*max = stat.st_size;
		/* TODO: potentially optimize to eliminate unnecessary
		   if checks
		*/
		switch (forder)
		{
		case 1:
			alpha_insert_in_vfinfo(vfinfo_dp, path->str, stat);
			break;
		case -1:
			ralpha_insert_in_vfinfo(vfinfo_dp, path->str, stat);
			break;
		case 2:
			size_insert_in_vfinfo(vfinfo_dp, path->str, stat);
			break;
		case -2:
			rsize_insert_in_vfinfo(vfinfo_dp, path->str, stat);
			break;
		}
	}
	free(dpath);
	return (0);
}

/**
 * alpha_insert_in_vfinfo - insert new node in vfinfo linked list by name of file
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @fname: file name to store in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int alpha_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;
	vfinfo_t *vfi_node_prev;

	/* printf("DB: --- alpha_insert_in_vfinfo\n"); */

	vfi_node = *vfinfo_dp;

	if (vfi_node == NULL || fname_precedes(fname, vfi_node->name))
		return (add_vfi_node(vfinfo_dp, fname, stat));

	while (vfi_node != NULL)
	{
		if (fname_precedes(fname, vfi_node->name))
			break;					 
		vfi_node_prev = vfi_node;
		vfi_node=vfi_node->next;
	}

	insert_vfi_node(vfi_node_prev, fname, stat);

	return (0);
}

/**
 * ralpha_insert_in_vfinfo - insert new node in reverse sorted vfinfo list by
 * name of file
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @fname: file name to store in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int ralpha_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;
	vfinfo_t *vfi_node_prev;

	/* printf("DB: --- alpha_insert_in_vfinfo\n"); */

	vfi_node = *vfinfo_dp;

	if (vfi_node == NULL || fname_precedes(fname, vfi_node->name) == 0)
		return (add_vfi_node(vfinfo_dp, fname, stat));

	while (vfi_node != NULL)
	{
		if (fname_precedes(fname, vfi_node->name) == 0)
			break;					 
		vfi_node_prev = vfi_node;
		vfi_node=vfi_node->next;
	}

	insert_vfi_node(vfi_node_prev, fname, stat);

	return (0);
}

/**
 * size_insert_in_vfinfo - insert new node in vfinfo linked list by size of
 * file first, then name
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @fname: file name to store in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int size_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;
	vfinfo_t *vfi_node_prev;

	vfi_node = *vfinfo_dp;

	if (vfi_node == NULL)
		return (add_vfi_node(vfinfo_dp, fname, stat));

	if (vfi_node->size < stat.st_size ||
	    (vfi_node->size == stat.st_size &&
	     fname_precedes(fname, vfi_node->name)))
	{
		add_vfi_node(vfinfo_dp, fname, stat);
		(*vfinfo_dp)->next = vfi_node;
		return (0);
	}

	while (vfi_node->size >= stat.st_size)
	{
		if (vfi_node->size == stat.st_size && fname_precedes(fname, vfi_node->name))
			break;
		vfi_node_prev = vfi_node;
		if (vfi_node->next == NULL)
			break;
		vfi_node = vfi_node->next;
	}
	insert_vfi_node(vfi_node_prev, fname, stat);

	return (0);
}

/**
 * size_insert_in_vfinfo - insert new node in vfinfo linked list by size of
 * file first, then name
 * @vfinfo_dp: ptr to ptr to head of vfinfo linked list
 * @fname: file name to store in new node
 * @stat: stat buffer containing file details to store in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int rsize_insert_in_vfinfo(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;
	vfinfo_t *vfi_node_prev;

	vfi_node = *vfinfo_dp;

	if (vfi_node == NULL)
		return (add_vfi_node(vfinfo_dp, fname, stat));

	if (vfi_node->size > stat.st_size)
	{
		add_vfi_node(vfinfo_dp, fname, stat);
		(*vfinfo_dp)->next = vfi_node;
		return (0);
	}

	while (vfi_node->size <= stat.st_size)
	{
		vfi_node_prev = vfi_node;
		if (vfi_node->next == NULL)
			break;
		vfi_node = vfi_node->next;
	}
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

	vfi_node_new = get_vfi_node(fname, stat);
	if (vfi_node_new == NULL)
		return (2);

	vfi_node_new->next = vfi_node_prev->next;
	vfi_node_prev->next = vfi_node_new;
	return (0);
}

/**
 * add_vfi_node - add a vfinfo node as head to linked vfinfo list
 * @vfinfo_dp: pointer to ptr to head of linked vfinfo list
 * @fname: file name to store in vfinfo node
 * @stat: file info to store in vfinfo node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int add_vfi_node(vfinfo_t **vfinfo_dp, char *fname, struct stat stat)
{
	vfinfo_t *vfinfo_old;

	vfinfo_old = *vfinfo_dp;
	*vfinfo_dp = get_vfi_node(fname, stat);
	if (*vfinfo_dp == NULL)
		return (2);

	(*vfinfo_dp)->next = vfinfo_old;
	return (0);
}

/**
 * get_vfi_node - create a vfinfo node for linked vfinfo list
 * @fname: file name to store in vfinfo node
 * @stat: file info to store in vfinfo node
 *
 * Return: ptr to new node, (NULL in case of malloc failure)
 */
vfinfo_t *get_vfi_node(char *fname, struct stat stat)
{
	vfinfo_t *vfi_node;

	vfi_node = malloc(sizeof(vfinfo_t));
	if (vfi_node == NULL)
		return (NULL);

	/* TOCHECK: is using the og values ok for ptrs, or should i use
	   copy_str? copy_str is necessary if I want to know that I need char *
	   freeing at end? */
	vfi_node->name = fname; /* TODO: fix copy_str? */
	vfi_node->size = stat.st_size;
	vfi_node->perm = get_pstrv(stat.st_mode);
	if (vfi_node->perm == NULL)
		return (NULL);
	vfi_node->nlink = stat.st_nlink;
	vfi_node->uid = getpwuid(stat.st_uid)->pw_name; /* TODO: handle undef'd */
	vfi_node->gid = getgrgid(stat.st_gid)->gr_name; /* TODO: handle undef'd */
	vfi_node->mtime = ctime(&(stat.st_mtime));
	vfi_node->next = NULL;

	return (vfi_node);
}

/**
 * get_pstrv - get permission string for given st_mode/file perms
 * @mode: code for file perms
 *
 * Return: pointer to string representing file perms
 */
char *get_pstrv(int mode)
{
	char *pstr;

	pstr = malloc(sizeof('c')*11);
	if (pstr == NULL)
		return NULL;

	pstr[0] = (S_ISDIR(mode)) ? 'd':'-';
	pstr[1] = (mode & S_IRUSR) ? 'r':'-';
	pstr[2] = (mode & S_IWUSR) ? 'w':'-';
	pstr[3] = (mode & S_IXUSR) ? 'x':'-';
	pstr[4] = (mode & S_IRGRP) ? 'r':'-';
	pstr[5] = (mode & S_IWGRP) ? 'w':'-';
	pstr[6] = (mode & S_IXGRP) ? 'x':'-';
	pstr[7] = (mode & S_IROTH) ? 'r':'-';
	pstr[8] = (mode & S_IWOTH) ? 'w':'-';
	pstr[9] = (mode & S_IXOTH) ? 'x':'-';
	pstr[10] = '\0';

       	return (pstr);
}

/**
 * free_vfinfo - free nodes in vfinfo linked list
 * @vfinfo: ptr to head of vfinfo linked list
 *
 * Return: 0 for success
 */
int free_vfinfo(vfinfo_t *vfinfo)
{
	vfinfo_t *node;

	/* printf("DB: -- free_vfinfo\n"); */

	while (vfinfo != NULL)
	{
		node = vfinfo;
		vfinfo = node->next;
		free(node->perm);
		free(node);

	}

	return (0);
}
