#include "../includes/struct.h"
#include "../includes/print.h"

void	*set_prev_in_nei_of_lop (t_list_of_paths *lop, void *pre)
{
	t_neighbour	*temp;
	
	temp = lop->path;
	while (temp)
	{
		temp->prev = (t_neighbour*)pre;
		pre = (void*)temp;
		temp = temp->next;
	}
	return ((void*)lop);
}

void	*set_used_in_nei_rooms (t_neighbour *nei, void *nb)
{
	if (nei->room)
		nei->room->used = *(int*)nb;
	return (nei);
}

void	*set_used_in_lop_rooms (t_list_of_paths *lop, void *nb)
{
	int	n;
	
	if (nb)
		n = *(int*)nb;
	else
		n = 0;
	browse_nei (lop->path, (void*)&n, &set_used_in_nei_rooms);
	return ((void*)lop);
}
