#include <stdlib.h>
#include <unistd.h>
#include "../includes/get_next_line.h"
#include "../includes/exit.h"
#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/visual.h"
#include "../includes/visual_struct.h"

static void	reajust_max_coord (t_room *room, int (*max_coord)[4])
{
	if ((*max_coord)[0] == 2147483647 || room->XCOORD < (*max_coord)[0] + 1)
		(*max_coord)[0] = room->XCOORD - 1;
	if ((*max_coord)[1] == 2147483647 || room->XCOORD > (*max_coord)[1] - 1)
		(*max_coord)[1] = room->XCOORD + 1;
	if ((*max_coord)[2] == 2147483647 || room->YCOORD < (*max_coord)[2] + 1)
		(*max_coord)[2] = room->YCOORD - 1;
	if ((*max_coord)[3] == 2147483647 || room->YCOORD > (*max_coord)[3] - 1)
		(*max_coord)[3] = room->YCOORD + 1;
}

static void	add_true_room (char *line, int is_start_end,
				t_sorttree *tree, int (*max_coord)[4])
{
	int				namelen;
	char			*name;
	t_room			*this_room;
	
	namelen = ft_strlen (line);
	if (!(name = (char*)malloc(sizeof(char) * ((namelen) + 1)))
		|| !(this_room = (t_room*)malloc(sizeof(t_room))))
	{
		free (name);
		return;
	}
	while (line[--(namelen)] != ' ');
	this_room->YCOORD = ft_atoi(line + namelen);
	while (line[--(namelen)] != ' ');
	this_room->XCOORD = ft_atoi(line + namelen);
	reajust_max_coord (this_room, max_coord);
	name = ft_strncpy (name, line, (namelen));
	name[(namelen)] = 0;
	this_room->name = name;
	this_room->status = is_start_end;
	this_room->neighbour = NULL;
	sort_room_like_hotrace (this_room, tree);
}

void	visual_get_rooms(char **aline, t_sorttree **atree, int (*max_coord)[4])
{
	int	status;
	
	status = 0;
	*atree = new_sorttree ();
	while (get_next_line_lemin (0, aline) && (is_room (*aline)
		|| is_start_end(*aline) || is_comment(*aline)))
	{
		if (!(*aline))
			exit_msg ((char*)("ERROR"), 5);
		if (!status && is_start_end (*aline))
			status = is_start_end (*aline);
		if (is_room (*aline))
		{
			add_true_room(*aline, status, *atree, max_coord);
			status = 0;
		}
		free (*aline);
	}
}
