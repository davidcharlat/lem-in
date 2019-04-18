#include <stdlib.h>
#include <unistd.h>
#include "../includes/get_next_line.h"
#include "../includes/exit.h"
#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"

static void	add_true_room (char *line, int is_start_end, t_sorttree *tree)
{
	int		namelen;
	char	*name;
	t_room	*this_room;
	
	namelen = ft_strlen (line);
	while (line[--(namelen)] != ' ');
	while (line[--(namelen)] != ' ');
	if (!(name = (char*)malloc(sizeof(char) * ((namelen) + 1)))
		|| !(this_room = (t_room*)malloc(sizeof(t_room))))
	{
		free (name);
		return;
	}
	name = ft_strncpy (name, line, (namelen));
	name[(namelen)] = 0;
	this_room->name = name;
	this_room->used = 0;
	this_room->status = is_start_end;
	this_room->nb_of_neighbour = 0;
	this_room->neighbour = NULL;
	sort_room_like_hotrace (this_room, tree);
}

void	get_rooms(char **aline, t_sorttree **atree)
{
	int	status;
	
	status = 0;
	*atree = new_sorttree ();
	while (get_print_next_line (0, aline) && (is_room (*aline)
		|| is_start_end(*aline) || is_comment(*aline)))
	{
		if (!(write (1, "\n", 1)) || !(*aline))
			exit_msg ((char*)("ERROR"), 5);
		if (!status && is_start_end (*aline))
			status = is_start_end (*aline);
		if (is_room (*aline))
		{
			add_true_room(*aline, status, *atree);
			status = 0;
		}
		free (*aline);
	}
		if (!(write (1, "\n", 1)))
			exit_msg ((char*)("ERROR"), 5);
}
