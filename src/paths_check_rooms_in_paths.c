#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/get.h"
#include "../includes/libft.h"
#include "../includes/exit.h"
	#include <stdio.h>

void	clear_tree (t_sorttree *tree, t_neighbour *path, t_room *room)
{
	t_room	*temp;
	
	while (path && path->room != room)
	{
		if (path->room && (temp = find_room (tree, path->room->name,
			ft_strlen (path->room->name))))
//{printf ("remise à zero: %s\n", temp->name);
			temp->used = 0;
//}
		path = path->next;
	}
//	if (path && path->room && (temp = find_room (tree, path->room->name,
//			ft_strlen (path->room->name))))
//{printf ("remise finale à zero: %s\n", temp->name);
//		temp->used = 0;
//}
}

int		test_new_path (t_sorttree *tree, t_neighbour *path)
{
	t_room		*temp;
	t_neighbour	*pcpy;
	
	pcpy = path;
	while (pcpy)
	{
		if (pcpy->room && (temp = find_room (tree, pcpy->room->name,
			ft_strlen (pcpy->room->name))))
		{
//printf ("%s ",pcpy->room->name);
			if (temp->used && temp->status != 1)
			{
//printf("allready used\n");
				clear_tree (tree, path, temp);
				return (0);
			}
			temp->used = 1;
		}
		pcpy = pcpy->next;
	}
//printf ("ok\n");
	return (1);
}
