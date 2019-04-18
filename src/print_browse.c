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
