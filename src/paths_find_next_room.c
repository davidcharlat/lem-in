#include <stdlib.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/exit.h"
	#include <stdio.h>

static int	verify (t_tree_of_paths *tree, t_po_sons_in_top	*poson)
{
	t_room	*room;
	
	room = poson->this_son;
//printf("in room %s, testing room %s\n", tree->room->name, room->name);
	while (tree && tree->parent)
	{
//printf("searching room %s in posons of room %s\n", room->name, tree->parent->room->name);
		if (tree->room == room || tree->parent->room == room 
			|| find_room_in_po_sons (tree->parent, room))
		{
//printf("room %s found in uncles\n", room->name);
			poson->is_still_possible = 0;
			return (0);
		}
		tree = tree->parent;
	}
	return (1);
}

t_room		*find_next_room (int i, t_tree_of_paths *tree)
{
	int					nth;
	t_po_sons_in_top	*temp_poson;
	t_po_sons_in_top	*temp_poson_cpy;
	
	temp_poson = tree->possible_sons;
	if (!tree->still_possible_son)
		return (NULL);
	nth = i % tree->room->nb_of_neighbour;
	while (nth-- && temp_poson)
		temp_poson = temp_poson->next_son;
	temp_poson_cpy = temp_poson;
	while (temp_poson)
	{
//printf ("f next room: testing room: %s\n", temp_poson->this_son->name);
		if (temp_poson->is_still_possible && verify(tree, temp_poson)) //verify(tree,temposon) doit verify que poson est un chemin acceptable
//{printf ("f next room: %s\n", temp_poson->this_son->name);
			return (temp_poson->this_son);
//}
		temp_poson = temp_poson->next_son;
	}
	temp_poson = tree->possible_sons;
	while (temp_poson && temp_poson != temp_poson_cpy)
	{
		if (temp_poson->is_still_possible && verify(tree, temp_poson)) //verify(tree,temposon) doit verify que poson est un chemin acceptable
//{printf ("f next room: %s\n", temp_poson->this_son->name);
			return (temp_poson->this_son);
//}
		temp_poson = temp_poson->next_son;
	}
	return (NULL);
}


