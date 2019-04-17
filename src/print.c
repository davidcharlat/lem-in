#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/print.h"
		#include <stdio.h>

void	*print_one_step (t_list_of_paths *lop, void *ant_ptr)
{
//	int			done;
//	int			ants_gone;
//	int			i;
	t_neighbour	*nei;
	
//	todo = *(int*)ant_ptr;
//	i = 0;
	nei = lop->path;
//printf ("nei done\n");
	while (nei && nei->room && nei->room->used)
//{printf ("to next room\n");
		nei = nei->next;
//}
//printf ("last ant found\n");
//printf ("nei%p\n", nei);
	while (nei && nei->prev && nei->prev->room)
	{
//printf ("ants advancing\n");
		if (nei->room && nei->prev->room->used)
		{
			if(nei->room->status != 1)
			{
				nei->room->used = nei->prev->room->used;
				if (nei->room->used > 0)
printf ("L%d-%s ",nei->room->used, nei->room->name);/*
			print_one_ant (nei->room->used, nei->room->name);  //void print_one_ant (int ant, char *room), affiche seulement si ant >0
*/
			}
			else if (nei->prev->room->used > 0)
printf ("L%d-%s ",nei->prev->room->used, nei->room->name);/*
			print_one_ant (nei->prev->room->used, nei->room->name);  //void print_one_ant (int ant, char *room), affiche seulement si ant >0
*/
		}
		nei = nei->prev;
	}
	if (nei && !nei->prev && *((int*)ant_ptr) < *(((int*)ant_ptr) + 1) && lop->lenght)
	{
//printf("%d ants have mooved\n", (*((int*)ant_ptr)));
		nei->room->used = ++(*((int*)ant_ptr));
		lop->lenght--;
printf ("L%d-%s ",nei->room->used, nei->room->name);/*
			print_one_ant (nei->room->used, nei->room->name);  //void print_one_ant (int ant, char *room), affiche seulement si ant >0
*/
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
if (lop->path)
printf ("%d ants in tunnel starting at %s\n", lop->lenght, lop->path->room->name);
	return ((void*)(lop));
}
		
void	*lenght_to_ants (t_list_of_paths *lop, void *astepnb)
{
	if (lop->lenght < *(int*)astepnb)
		lop->lenght = *(int*)astepnb - lop->lenght;
	else
	 	lop->lenght = 0;
if (lop->path)
printf ("%d ants in tunnel starting at %s\n", lop->lenght, lop->path->room->name);
	return ((void*)(lop));
}

void	print_paths (t_list_of_paths *lop, t_sorttree *tree, int nb_of_ants)
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
printf ("%d step, %d path\n",ptr[0], pathnb);
	browse_lop (lop, &(ptr[0]), &lenght_to_ants);
	browse_lop (lop, &nb_of_ants, &rectify_ants);
	browse_lop (lop, NULL, &set_used_in_lop_rooms);
	browse_lop (lop, NULL, &set_prev_in_nei_of_lop);
	while (ptr[0] > ptr[1])
	{
printf ("step %d/%d\n", ptr[1], ptr[0]);
		browse_lop (lop, &(ptr[2]), &print_one_step);
		ptr[1]++;
printf ("\n");
/*		
		ft_putchar ('\n');
*/
	}
}	
