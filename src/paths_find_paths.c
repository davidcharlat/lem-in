#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/exit.h"
#include "../includes/free.h"

static int			start_beside_end (t_room *start)
{
	t_neighbour	*temp;
	
	temp = start->neighbour;
	while (temp)
	{
		if (temp->room && temp->room->status == 2)
			return (1);
		temp = temp->next;
	}
	return (0);	
}

static void			close_path_in_top (t_tree_of_paths *top)
{
	t_po_sons_in_top	*tempps;
	t_sons_in_top		*temps;
	
	tempps = NULL;
	temps = NULL;
	(top->parent->still_possible_son)--;
	if (top->parent->sons && top->parent->possible_sons)
	{
		temps = top->parent->sons;
		while (temps && temps->this_son != top)
			temps = temps->next_son;
		if (temps)
			temps->is_still_possible = 0;
		tempps = top->parent->possible_sons;
		while (tempps && tempps->this_son != top->room)
			tempps = tempps->next_son;
		if (tempps)
			tempps->is_still_possible = 0;
	}
}

int				find_1path (int i, t_list_of_paths **alop,
					t_tree_of_paths *top)
{
	t_room			*next_room;
	t_tree_of_paths *next_top;
	
	if (i)
		i--;
	if (top && top->room->status == 3)
	{
		close_path_in_top (top);
		return (add_1path (alop, top));
	}														
	if (!(next_room = find_next_room (i, top)))
	{
		if (!top || (top)->room->status == 1 || !top->parent)
			return (0);
		close_path_in_top (top);
		return (find_1path (i, alop, top->parent));
	}
	if ((next_top = find_room_in_sons (top, next_room)))
		return (find_1path (i, alop, next_top));
	if ((next_top = add_son_in_top (next_room, top)))
		return (find_1path (i, alop, next_top));
	return (1);
}

t_list_of_paths	*find_paths (t_room *start)
{
	t_list_of_paths	*ret;
	t_tree_of_paths	*top;
	int				i;
	
	i = 0;
	if (start_beside_end (start))
		exit_msg ((char*)("ERROR, exit is beside start"), 27);
	if (!(ret = (t_list_of_paths*)malloc(sizeof(t_list_of_paths))))
		exit_msg ((char*)("ERROR"), 5);
	ret->path = NULL;
	ret->lenght = 0;
	ret->next = NULL;
	if (!fill_node_of_top (&top, start, NULL))
		exit_msg ((char*)("ERROR"), 5);
	while (i < NB_OF_PATHS && find_1path (i, &ret, top))
		i++;
	free_top (top);
	return (ret);
}
