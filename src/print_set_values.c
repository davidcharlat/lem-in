#include "../includes/struct.h"
#include "../includes/print.h"
		#include <stdio.h>

void	*set_prev_in_nei_of_lop (t_list_of_paths *lop, void *nb)
{
	t_neighbour *prev;
	t_neighbour	*temp;
	
	prev = (void*)0;
	temp = lop->path;
	while (temp)
	{
if (temp->room)
printf ("room %s, add %p has prev: %p\n", temp->room->name, temp, prev);
		temp->prev = prev;
		prev = temp;
		temp = temp->next;
	}
printf ("end of set previous\n");
}

void	*set_used_in_nei_rooms (t_neighbour *nei, void *nb)
{
	if (nei->room)
		nei->room->used = *(int*)nb;
if (nei->room)
printf ("room %s, used: %d\n", nei->room->name, nei->room->used);
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
	return (lop);

}
