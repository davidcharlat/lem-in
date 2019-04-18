#include "../includes/struct.h"
#include "../includes/get.h"
#include <stdlib.h>

void	free_neighbour (t_neighbour *nei)
{
	t_neighbour	*temp;
	
	while (nei)
	{
		temp = nei;
		nei = nei->next;
		temp->room = NULL;
		temp->next = NULL;
		temp->prev = NULL;
		free (temp);
	}
}

void	free_lop (t_list_of_paths *lop, int free_neigh)
{
	t_list_of_paths	*temp;
	
	while (lop)
	{
		temp = lop;
		if (free_neigh)
		{
			free_neighbour (temp->path);
			temp->path = NULL;
		}
		lop = lop->next;
		free (temp);
	}
}

void	free_test (t_test_paths *test)
{
	t_test_paths	*temp;
	
	while (test)
	{
		temp = test;
		test = test->next;
		free (temp);
	}
}

void	free_top (t_tree_of_paths *top)
{
	t_sons_in_top 		*sons[2];
	t_po_sons_in_top	*posons[2];
	
	if (top && top->possible_sons)
	{
		posons[0] = top->possible_sons;
		while (posons[0] && posons[0]->this_son)
		{
			posons[1] = posons[0]->next_son;
			free (posons[0]);
			posons [0] = posons[1];
		}
	}
	if (top && top->sons)
	{
		sons[0] = top->sons;
		while (sons[0] && sons[0]->this_son)
		{
			free_top (sons[0]->this_son);
			sons[1] = sons[0]->next_son;
			free (sons[0]);
			sons [0] = sons[1];
		}
	}
	free (top);
}

void	free_tree (t_sorttree *tree)
{
	int i;
	
	i = -1;
	if (tree)
	{
		while (i++ < NUMBEROFLEAVES - 1)
		{
			if (tree->next[i])
				free_tree (tree->next[i]);
		}
		free ((tree->cont).room_name);
		if ((tree->cont).sroom)
			free_neighbour (((tree->cont).sroom)->neighbour);
		free ((tree->cont).sroom);
		free (tree);
	}
}

