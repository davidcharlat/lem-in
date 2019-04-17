#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/exit.h"
#include "../includes/free.h"
	#include <stdio.h>

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
//printf ("close path with top room %s, son of %s which has %d posons\n", top->room->name, top->parent->room->name, top->parent->still_possible_son);
//printf ("adress: parent sons: %p & parent possons %p, parnt: %s\n",top->parent->sons, top->parent->possible_sons, top->parent->room->name );
	(top->parent->still_possible_son)--;
	if (top->parent->sons && top->parent->possible_sons)
	{
		temps = top->parent->sons;
		while (temps && temps->this_son != top)
//{printf ("testing temps this son room %p\n", temps->this_son->room);
//printf ("tested son %p of parent\n", temps->this_son->room->name);
			temps = temps->next_son;
//}
		if (temps)
//{printf ("is no more possible in sons: %s\n", temps->this_son->room->name);
			temps->is_still_possible = 0;
//}
		tempps = top->parent->possible_sons;
		while (tempps && tempps->this_son != top->room)
//{printf ("tested poson %s of parent\n", tempps->this_son->name);
			tempps = tempps->next_son;
//}
		if (tempps)
//{printf ("is no more possible in posons: %s\n", tempps->this_son->name);
			tempps->is_still_possible = 0;
//}
	}
}

int				find_1path (int i, t_list_of_paths **alop,
					t_tree_of_paths *top)
{
	t_room			*next_room;
	t_tree_of_paths *next_top;
	
//printf ("find 1 path ith i =%d\n", i);
	if (i)
		i--;
	if (top && top->room->status == 3)
	{
//printf ("path found in find 1path\n");
		close_path_in_top (top);
		return (add_1path (alop, top));
	}														
	if (!(next_room = find_next_room (i, top)))
	{
//printf("fnr = NULL\n");	
		if (!top || (top)->room->status == 1 || !top->parent)
			return (0);
		close_path_in_top (top);
		return (find_1path (i, alop, top->parent));
	}
	if (next_top = find_room_in_sons (top, next_room))
		return (find_1path (i, alop, next_top));
	if (next_top = add_son_in_top (next_room, top))
		return (find_1path (i, alop, next_top));
	return (1);
}

t_list_of_paths	*find_paths (t_room *start)
{
	t_list_of_paths	*ret;
	t_tree_of_paths	*top;
	int				i;
t_neighbour *nei;
t_list_of_paths	*cpy;
	
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
cpy = ret;
while (cpy){ nei = cpy->path;
while (nei && nei->room){
printf ("%s - ", nei->room->name); nei = nei->next;}
printf ("     lenght: %d\n",cpy->lenght); cpy = cpy->next;}
	free_top (top);
	return (ret);
}
