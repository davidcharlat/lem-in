#include "../includes/libft.h"
#include "../includes/struct.h"
#include "../includes/get.h"
	#include <stdio.h>

int		is_tunnel(char *line, t_sorttree *tree)
{
	int	lenght;
	int	pos;
	
	lenght = ft_strlen(line);
	pos = lenght;
	if (line[0] == '#')
		return (1);
	while (--pos > 0 && line[pos] != '-');
	if (pos < 1)
{printf ("pos: %d line: %s, tunnel not found\n", pos, line);
	return (0);
}
	line[pos] = 0;
	if (find_room(tree, line, pos)
		&& find_room(tree, line + pos + 1, lenght - pos - 1))
	{
printf ("tunnel from %s to %s\n",(find_room(tree, line, pos))->name, (find_room(tree, line + pos + 1, lenght - pos - 1))->name);
		line[pos] = '-';
		return (1);
	}
printf ("line: %s, room not found\n", line);
	return (0);
}

int		is_room(char *line)
{
	int	lenght;
	int	is_coord;
	
	is_coord = 0;
	lenght = ft_strlen(line);
	if (line[0] == '#' || line[0] == 'L')
		return (0);
	while (--lenght > 0 && line[lenght] >= '0' && line[lenght] <= '9')
		is_coord = 1;
	if (line[lenght] == '-' || line[lenght] == '+')
		lenght--;
	if (line[lenght] != ' ' || !is_coord)
		return (0);
	is_coord = 0;
	while (--lenght > 0 && line[lenght] >= '0' && line[lenght] <= '9')
		is_coord = 1;
	if (line[lenght] == '-' || line[lenght] == '+')
		lenght--;
	if (line[lenght] != ' ' || !is_coord || lenght < 1)
		return (0);
	return (1);
}

int		is_comment (char *line)
{
	if ((ft_strcmp (line, "##start") || ft_strcmp (line, "##start")) 
		&& line[0] == '#')
		return (1);
	return (0);
}

int		is_start_end (char *line)
{
	if (!ft_strcmp (line, "##start"))
		return (2);
	else if (!ft_strcmp (line, "##end"))
		return (1);
	return (0);
}
