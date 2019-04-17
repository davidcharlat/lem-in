#include <unistd.h>
#include <stdlib.h>
#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/get_next_line.h"
	#include <stdio.h>


static int	find_tunnel (t_room *room1, t_room *room2)
{
	t_neighbour	*temp;
	
	if (!room1 || !room2)
		return (1);
	temp = room1->neighbour;
	while (temp)
	{
		if (temp->room == room2)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static void	add_1tunnel (t_room *room1, t_room *room2)
{
	t_neighbour	*nei;
	t_neighbour	*find;
	
	if (!(nei = (t_neighbour*)malloc(sizeof(t_neighbour))))
		return;
	nei->room = room2;
	nei->next = NULL;
	if (room1->status == 0 && room2->status == 2)
		room1->status = 3;
	(room1->nb_of_neighbour)++;
	if (!(room1->neighbour))
	{
		room1->neighbour = nei;
printf ("created neighbour %s\n", room1->neighbour->room->name);
printf ("room %s has now %d neighbour(s)\n\n", room1->name, room1->nb_of_neighbour);
		return;
	}
	find = room1->neighbour;
printf("neighbours: %s ", find->room->name);
	while (find->next)
{
		find = find->next;
printf(" %s ;", find->room->name);
}
printf ("created neighbour %s\n", nei->room->name);
	find->next = nei;
printf ("room %s (status: %d) has now %d neighbour(s)\n\n", room1->name, room1->status, room1->nb_of_neighbour);
}

void	get_tunnels(char **aline, t_sorttree **atree)
{
	int		len;
	int		pos;
	t_room	*r1;
	t_room	*r2;

	while (is_tunnel (*aline, *atree) || (*aline && (*aline)[0] == '#'))
	{
		len = ft_strlen(*aline);
		pos = len;
		while (--pos > 0 && (*aline)[pos] != '-');
			(*aline)[pos] = 0;
		r1 = find_room (*atree, *aline, pos);
		r2 = find_room (*atree, (*aline) + pos + 1, len - pos - 1);
		if ((*aline)[0] != '#' && r1 != r2 && !find_tunnel(r1, r2))
		{
			add_1tunnel (r1, r2);
			add_1tunnel (r2, r1);
		}
		free (*aline);
		get_print_next_line (0, aline);
	}
	free (*aline);
	while (get_print_next_line (0, aline))
		free (*aline);
	free (*aline);
}

/*	#include "../includes/libft.h"
	#include "../includes/classify_lines.h"
#include "../includes/add_room.h"
#include "../includes/neighbour.h"
#include "../includes/find_room.h"
#include "../includes/sorttree.h"
#include <stdlib.h>
	#include <stdio.h>

static int	add_1tunnel (t_room *room1, t_room *room2)
{
	t_neighbour	*nei;
	t_neighbour	*find;
	
	if (!(nei = (t_neighbour*)malloc(sizeof(t_neighbour))))
		return (0);
	nei->room = room2;
	nei->next = NULL;
	if (room1->status > 1 && room2->status == 1)
		room1->status = 3;
	(room1->nb_of_neighbour)++;
	if (!(room1->neighbour))
	{
		room1->neighbour = nei;
printf ("created neighbour %s\n", room1->neighbour->room->name);
printf ("room %s has now %d neighbour(s)\n\n", room1->name, room1->nb_of_neighbour);
		return (1);
	}
	find = room1->neighbour;
printf("neighbours: %s ", find->room->name);
	while (find->next)
{
		find = find->next;
printf(" %s ;", find->room->name);
}
printf ("created neighbour %s\n", nei->room->name);
	find->next = nei;
printf ("room %s (status: %d) has now %d neighbour(s)\n\n", room1->name, room1->status, room1->nb_of_neighbour);
	return (1);
}

int			add_tunnel(char **line, t_sorttree *tree)
{
	int	lenght;
	int	pos;
	int	ret;
	
	ret = 0;
	lenght = ft_strlen(*line);
	pos = lenght;
	write (1, *line, lenght);
	write (1,"\n",1);
	if ((*line)[0] == '#')
	{
		free (*line);
		return (1);
	}
	while (--pos > 0 && (*line)[pos] != '-');
	(*line)[pos] = 0;
	if (find_room(tree, *line, pos) 
		== find_room(tree, (*line) + pos + 1, lenght - pos - 1))
	{
		free (*line);
		return (1);
	}
	ret = add_1tunnel (find_room(tree, *line, pos),
			find_room(tree, (*line) + pos + 1, lenght - pos - 1))
		* add_1tunnel (find_room(tree, (*line) + pos + 1, lenght - pos - 1),
			find_room(tree, *line, pos));
	(*line)[pos] = '-';
	free (*line);
	return (ret);
}*/
