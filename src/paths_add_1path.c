#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/exit.h"

static int	lon_lenght (t_neighbour *path)
{
	int	i;
	
	i = 0;
	while (path)
	{
		path = path->next;
		i++;
	}
	return (i - 2);
}

static int	fill_nei_for_lop (t_tree_of_paths *leaf, t_neighbour *path)
{
	t_neighbour *temp;
	
	temp = path;
	while (leaf)
	{
		if (!(temp->next = (t_neighbour*)malloc (sizeof(t_neighbour))))
			return (0);
		temp->room = leaf->room;
		temp = temp->next;
		leaf = leaf->parent;
	}
	temp->next = NULL;
	temp->room = NULL;
	return (1);
}

int			add_1path (t_list_of_paths **alist, t_tree_of_paths *leaf)
{
	t_list_of_paths	*temp;
	t_list_of_paths	*new;
	t_neighbour		*path;
	
	if (!(new = (t_list_of_paths*)malloc(sizeof(t_list_of_paths))))
		return (0);
	if (!(path = (t_neighbour*)malloc(sizeof(t_neighbour)))
		|| !fill_nei_for_lop(leaf, path))
		return (0);
	if (!((*alist)->path))
	{
		(*alist)->path = path;
		(*alist)->lenght = lon_lenght (path);
		free (new);
		return (1);
	}
	new->path = path;
	new->lenght = lon_lenght(path);
	new->next = NULL;
	temp = *alist;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (1);
}
