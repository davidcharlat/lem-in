#include "../includes/struct.h"

void	browse_lop (t_list_of_paths *lop, void *ptr,
	void*(*f)(t_list_of_paths*, void*))
{
	while (lop)
	{
		f(lop, ptr);
		lop = lop->next;
	}
}

void	browse_nei (t_neighbour *nei, void *p, void*(*f)(t_neighbour*, void*))
{
	while (nei)
	{
		f(nei, p);
		nei = nei->next;
	}
}

void	*browse_tree (t_sorttree *tree, void *p, void*(*f)(t_sorttree*, void*))
{
	int 	i;
	void	*ptr;
	
	i = -1;
	if (tree)
	{
		while (i++ < NUMBEROFLEAVES - 1)
		{
			if (tree->next[i])
				ptr = (browse_tree(tree->next[i], p, f));
		}
		if ((tree->cont).sroom)
			return (f(tree, p));
		if (tree->level == 0)
			return ((void*)tree);
		return (ptr);
	}
	return ((void*)tree);
}
