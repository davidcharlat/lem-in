#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/get.h"
#include "../includes/exit.h"

t_po_sons_in_top	*find_room_in_po_sons (t_tree_of_paths *node, t_room *room)
{
	t_po_sons_in_top	*temps;

	temps = NULL;
	if (node && node->possible_sons)
		temps = node->possible_sons;	
	while (temps && temps->this_son)
	{
		if (temps->this_son == room)
			return (temps);
		temps = temps->next_son;
	}
	return (NULL);
}

t_tree_of_paths		*find_room_in_sons (t_tree_of_paths *node, t_room *room)
{
	t_sons_in_top	*temps;

	temps = NULL;
	if (node && node->sons)
		temps = node->sons;	
	while (temps && temps->this_son)
	{
		if (temps->this_son->room == room)
			return (temps->this_son);
		temps = temps->next_son;
	}
	return (NULL);
}

static void	put_find_start (t_sorttree *tree, t_room **astart)
{
	int i;
	
	i = -1;
	if (tree)
	{
		if (((tree->cont).sroom) && ((tree->cont).sroom)->status == 1)
		{
			*astart = (tree->cont).sroom;
			return;
		}
		while (i++ < NUMBEROFLEAVES - 1)
		{
			if (tree->next[i])
				put_find_start (tree->next[i], astart);
		}
		if (tree->level == 0)
			return;
	}
}

void		find_start (t_sorttree *tree, t_room **astart)
{
	*astart = NULL;
	put_find_start (tree, astart);
	if (!(*astart))	
		exit_msg ((char*)("ERROR, no room 'end'"), 20);
}

