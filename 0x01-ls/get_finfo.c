#include "hls-components.h"

/**
 * get_finfo - store filename and size in finfo linked list
 * @finfo_dp: ptr to ptr to head of finfo linked list
 * @dpath: path of directory containing files represented by finfo linked list
 * @fpaths_dp: ptr to ptr to head of filename linked list
 *
 * Return: 0 for success
 */
int get_finfo(finfo_t **finfo_dp, char *dpath, List **fpaths_dp, int forder)
{
	List *path;
	struct stat stat;

	if (dpath[get_len(dpath) - 1] != '/')
		dpath = strconcat(dpath, "/");
	/* TODO: free allocated dpath? */

	for (path = *fpaths_dp; path != NULL; path = path->next)
	{
		/* query lstat for file size */
		lstat(strconcat(dpath, path->str), &stat);
		(forder == 2) ? size_insert_in_finfo(finfo_dp, path->str, stat.st_size):
			rsize_insert_in_finfo(finfo_dp, path->str, stat.st_size);
	}
	return (0);
}


/**
 * size_insert_in_finfo - insert new node in finfo linked list by size of file
 * @finfo_dp: ptr to ptr to head of finfo linked list
 * @fname: file name to store in new node
 * @fsize: file size to store in new node
 *
 * Return: 0 for success, (tbi - 2 for malloc failure)
 */
int size_insert_in_finfo(finfo_t **finfo_dp, char *fname, int fsize)
{
	finfo_t *fi_node;
	finfo_t *fi_node_prev;

	/* printf("DB: size_insert_in_finfo\n"); */

	fi_node = *finfo_dp;
	fi_node_prev = NULL;

	if (fi_node == NULL)
		return (add_fi_node(finfo_dp, fname, fsize));

	if (fi_node->size < fsize ||
	    (fi_node->size == fsize && fname_precedes(fname, fi_node->name)))
	{
		add_fi_node(finfo_dp, fname, fsize);
		(*finfo_dp)->next = fi_node;
		return (0);
	}

	while (fi_node->size >= fsize)
	{
		if (fi_node->size == fsize &&
		    fname_precedes(fname, fi_node->name))
			break;
		fi_node_prev = fi_node;
		if (fi_node->next == NULL)
			break;
		fi_node = fi_node->next;
	}
	insert_fi_node(fi_node_prev, fname, fsize);

	return (0);
}

/**
 * rsize_insert_in_finfo - insert new node in finfo linked list by size of file
 * @finfo_dp: ptr to ptr to head of finfo linked list
 * @fname: file name to store in new node
 * @fsize: file size to store in new node
 *
 * Return: 0 for success, (tbi - 2 for malloc failure)
 * Description: finfo linked list is a linked list of file name and file size
 * already sorted by name.
 */
int rsize_insert_in_finfo(finfo_t **finfo_dp, char *fname, int fsize)
{
	finfo_t *fi_node;
	finfo_t *fi_node_prev;

	fi_node = *finfo_dp;

	if (fi_node == NULL)
		return (add_fi_node(finfo_dp, fname, fsize));

	/* TOCHECK: does this fxn need alphasort logic if list is
	   already sorted? if not, why does size_insert_in need it?
	*/

	if (fi_node->size > fsize)
	{
		add_fi_node(finfo_dp, fname, fsize);
		(*finfo_dp)->next = fi_node;
		return (0);
	}

	while (fi_node->size <= fsize)
	{
		fi_node_prev = fi_node;
		if (fi_node->next == NULL)
			break;
		fi_node = fi_node->next;
	}
	insert_fi_node(fi_node_prev, fname, fsize);

	return (0);
}

/**
 * insert_fi_node - insert a new finfo node after @fi_node_prev
 * @fi_node_prev: ptr to the node after which new node will be inserted
 * @fname: file name to be stored in new node
 * @fsize: file size to be stored in new node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int insert_fi_node(finfo_t *fi_node_prev, char *fname, int fsize)
{
	finfo_t *fi_node_new;

	fi_node_new = malloc(sizeof(finfo_t));
	if (fi_node_new == NULL)
	{
		perror("malloc");
		return (2);
	}

	fi_node_new->name = fname;
	fi_node_new->size = fsize;
	fi_node_new->next = fi_node_prev->next;

	fi_node_prev->next = fi_node_new;
	return (0);
}

/**
 * add_fi_node - add a finfo node to linked finfo list
 * @finfo_dp: pointer to ptr to head of linked finfo list
 * @fname: file name to store in finfo node
 * @fsize: file size to store in finfo node
 *
 * Return: 0 for success, 2 for malloc failure
 */
int add_fi_node(finfo_t **finfo_dp, char *fname, int fsize)
{
	finfo_t *fi_node;

	fi_node = malloc(sizeof(finfo_t));
	if (fi_node == NULL)
	{
		perror("malloc");
		return (2);
	}

	fi_node->name = copy_string(fname);
	fi_node->size = fsize;
	fi_node->next = *finfo_dp;

	*finfo_dp = fi_node;
	return (0);
}

/**
 * free_finfo - free nodes in finfo linked list
 * @vfinfo: ptr to head of finfo linked list
 *
 * Return: 0 for success
 */
int free_finfo(finfo_t *finfo)
{
	finfo_t *node;

	/* printf("DB: -- free_finfo\n"); */

	while (finfo != NULL)
	{
		node = finfo;
		finfo = node->next;
		free(node);
	}

	return (0);
}
