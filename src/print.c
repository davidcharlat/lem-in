#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/print.h"

void	print_one_ant (int ant, char *room)
{
	if (ant > 0)
	{
		ft_putchar ('L');
		ft_putnbr (ant);
		ft_putchar ('-');
		ft_putstr (room);
		ft_putchar (' ');
	}
}

void	*print_one_step (t_list_of_paths *lop, void *ptr)
{
	t_neighbour	*nei;
	
	nei = lop->path;
	while (nei && nei->room && nei->room->used)
		nei = nei->next;
	while (nei && nei->prev && nei->prev->room)
	{
		if (nei->room && nei->prev->room->used && nei->room->status != 1)
		{
				nei->room->used = nei->prev->room->used;
				print_one_ant (nei->room->used, nei->room->name);
		}
		else if (nei->room && nei->prev->room->used)
				print_one_ant (nei->prev->room->used, nei->room->name);
		nei = nei->prev;
	}
	if (nei && !nei->prev && *((int*)ptr) < *(((int*)ptr) + 1) && lop->lenght)
	{
		nei->room->used = ++(*((int*)ptr));
		lop->lenght--;
		print_one_ant (nei->room->used, nei->room->name);
	}
	else if (nei)
		nei->room->used = -1;
	return ((void*)(lop));
}

void	*rectify_ants (t_list_of_paths *lop, void *aantnb)
{
	if (lop->lenght > *(int*)aantnb)
	{
		lop->lenght = *(int*)aantnb;
		*(int*)aantnb = 0;
	}
	else
		*(int*)aantnb -= lop->lenght;
	return ((void*)(lop));
}
		
void	*lenght_to_ants (t_list_of_paths *lop, void *astepnb)
{
	if (lop->lenght < *(int*)astepnb)
		lop->lenght = *(int*)astepnb - lop->lenght;
	else
	 	lop->lenght = 0;
	return ((void*)(lop));
}

void	print_paths (t_list_of_paths *lop, int nb_of_ants)
{
	t_list_of_paths	*lcpy;
	int				ptr[4] = {0};
	int				pathnb;
	
	lcpy = lop;
	pathnb = -1;
	ptr[3] = nb_of_ants;
	while (lcpy)
	{
		ptr[0] = ptr[0] + lcpy->lenght;
		pathnb++;
		lcpy = lcpy->next;
	}
	ptr[0] = (nb_of_ants + ptr[0] - 1) / pathnb + 1;
	browse_lop (lop, &(ptr[0]), &lenght_to_ants);
	browse_lop (lop, &nb_of_ants, &rectify_ants);
	browse_lop (lop, NULL, &set_used_in_lop_rooms);
	browse_lop (lop, NULL, &set_prev_in_nei_of_lop);
	while (ptr[0] > ptr[1])
	{
		browse_lop (lop, &(ptr[2]), &print_one_step);
		ptr[1]++;
		ft_putchar ('\n');
	}
}	
