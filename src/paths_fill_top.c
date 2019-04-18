#include <stdlib.h>
#include <unistd.h>
#include "../includes/exit.h"
#include "../includes/struct.h"

static void			fill_po_son_with_nil (t_po_sons_in_top **poson,
	int i, t_room *room)
{
	(*poson)->this_son = room;
	(*poson)->is_still_possible = i;
	(*poson)->next_son = NULL;
}

t_po_sons_in_top	*fill_possible_sons (t_tree_of_paths **ato_fill,
						t_room *room)
{
	t_po_sons_in_top	*ret;
	t_po_sons_in_top	*temp;
	t_neighbour			*temp_nei;
	
	if (!(ret = (t_po_sons_in_top*)malloc(sizeof(t_po_sons_in_top))))
		return (NULL);
	fill_po_son_with_nil (&ret, 0, NULL);
	temp = ret;
	if ((temp_nei = room->neighbour))
	{
		while (temp_nei && temp)
		{
			fill_po_son_with_nil (&(temp),1 , temp_nei->room);
			temp_nei = temp_nei->next;
			if (temp_nei)
			{
				if ((temp->next_son
					= (t_po_sons_in_top*)malloc(sizeof(t_po_sons_in_top))))
					fill_po_son_with_nil (&(temp->next_son), 0, NULL);
				temp = temp->next_son;
			}
		}
	}
	(*ato_fill)->possible_sons = ret;
	return (ret);
}

t_tree_of_paths		*fill_node_of_top (t_tree_of_paths **ato_fill,
						t_room *room, t_tree_of_paths *parent)
{
	if (!((*ato_fill) = (t_tree_of_paths*)malloc (sizeof(t_tree_of_paths))))
		return (NULL);	
	if (!fill_possible_sons (ato_fill, room))
		return (NULL);
	(*ato_fill)->room = room;
	(*ato_fill)->parent = parent;
	(*ato_fill)->sons = NULL;
	(*ato_fill)->still_possible_son = room->nb_of_neighbour;
	return (*ato_fill);
}

t_tree_of_paths		*add_son_in_top (t_room *new_son, t_tree_of_paths *tree)
{
	t_sons_in_top	*temp;
	t_sons_in_top	*son;
	
	temp = tree->sons;
	if (!(son = (t_sons_in_top*)malloc(sizeof(t_sons_in_top))))
		return (NULL);
	son->next_son = NULL;
	son->is_still_possible = 1;
	son->this_son = fill_node_of_top (&(son->this_son), new_son, tree);
	while (temp && temp->next_son)
		temp = temp->next_son;
	if (!temp)
		tree->sons = son;
	else
		temp->next_son = son;
	return (son->this_son);
}
