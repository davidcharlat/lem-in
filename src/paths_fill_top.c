#include <stdlib.h>
#include <unistd.h>
#include "../includes/exit.h"
#include "../includes/struct.h"
	#include <stdio.h>

static void			fill_po_son_with_nil (t_po_sons_in_top **poson)
{
	(*poson)->this_son = NULL;
	(*poson)->is_still_possible = 0;
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
	fill_po_son_with_nil (&ret);
	temp = ret;
	if ((temp_nei = room->neighbour))
	{
		while (temp_nei && temp)
		{
//printf("creating possible son: %s\n", temp_nei->room->name);
			temp->is_still_possible = 1;
			temp->this_son = temp_nei->room;
			temp->next_son = NULL;
			temp_nei = temp_nei->next;
			if (temp_nei)
			{
				if (temp->next_son
					= (t_po_sons_in_top*)malloc(sizeof(t_po_sons_in_top)))
					fill_po_son_with_nil (&(temp->next_son));
				temp = temp->next_son;
			}
		}
	}
//printf ("1st possible son: %s, %d\n", ret->this_son->name, ret->is_still_possible);
//if(ret->next_son)printf ("2nd possible son: %s, %d\n", ret->next_son->this_son->name, ret->is_still_possible);	
	(*ato_fill)->possible_sons = ret;
//printf ("1st possible son: %s, %d\n", ret->this_son->name, ret->is_still_possible);	
//temp = (*ato_fill)->possible_sons;
//while (temp)
//{printf ("possible son: %s, %d\n", temp->this_son->name, temp->is_still_possible);
//temp = temp->next_son;
//}
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
//printf ("top created for room %s, tree: %p room: %p, parent: %p, sons: %p", room->name,*ato_fill, room, parent, (*ato_fill)->sons );
	(*ato_fill)->still_possible_son = room->nb_of_neighbour;
	return (*ato_fill);
}

t_tree_of_paths		*add_son_in_top (t_room *new_son, t_tree_of_paths *tree)
{
	t_sons_in_top	*temp;
	t_sons_in_top	*son;
	
//printf("add son %s\n", new_son->name);	
//printf("tree where to add son %p, named %s\n",tree, tree->room->name);
	temp = tree->sons;
///printf("actual address of tree->son %p\n",temp);
	if (!(son = (t_sons_in_top*)malloc(sizeof(t_sons_in_top))))
		return (NULL);
	son->next_son = NULL;
	son->is_still_possible = 1;
//printf ("son->is_still_possible = %d\n", son->is_still_possible);
	son->this_son = fill_node_of_top (&(son->this_son), new_son, tree);
//printf ("son->this_son done at address %p\n", son->this_son);
	while (temp && temp->next_son)
		temp = temp->next_son;
	if (!temp)
		tree->sons = son;
	else
		temp->next_son = son;
//printf("address where son has been added: %p\n",son);
	return (son->this_son);
}
