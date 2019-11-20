#include <unistd.h>
#include <stdlib.h>
#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/get_next_line.h"

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
		return;
	}
	find = room1->neighbour;
	while (find->next)
		find = find->next;
	find->next = nei;
}

void	get_tunnels(char **aline, t_sorttree **atree)
{
	int		len;
	int		pos;
	t_room	*r[2];

	while (is_tunnel (*aline, *atree) || (*aline && (*aline)[0] == '#'))
	{
		len = ft_strlen(*aline);
		pos = len;
		while (--pos > 0 && (*aline)[pos] != '-');
		(*aline)[pos] = 0;
		r[0] = find_room (*atree, *aline, pos);
		r[1] = find_room (*atree, (*aline) + pos + 1, len - pos - 1);
		if ((*aline)[0] != '#' && r[0] != r[1] && !find_tunnel(r[0], r[1]))
		{
			add_1tunnel (r[0], r[1]);
			add_1tunnel (r[1], r[0]);
		}
		free (*aline);
		get_print_next_line (0, aline);
		ft_putchar ('\n');
	}
	free (*aline);
}
