#include "../includes/libft.h"
#include "../includes/struct.h"
#include "../includes/get.h"
	#include <stdio.h>

int		is_move(char *line, t_sorttree *tree)
{
	int	lenght;
	int	pos;
	
	pos = ft_strlen(line);
printf("ismove? len: %d\n", pos);
	while (pos && line[pos - 1] == ' ')
	{
		line[pos - 1] = 0;
		pos--;
	}
	lenght = ft_strlen(line);
	while (--pos > 0 && line[pos] != '-');
printf("pos de - : %d\n", pos);
	if (pos < 2)
		return (0);
	if (!find_room(tree, line + pos + 1, lenght - pos - 1))
		return (0);
printf ("room found\n");
	if (line[pos] != '-')
		return (0);
	while (--pos > 0 && line[pos] >= '0' && line[pos] <= '9');
printf("pos de L : %d\n", pos);
	if (line[pos] != 'L')
		return (0);
	if (line[0] != 'L' || (line[1]) < '0' || (line[1]) > '9')
		return (0);
	return (1);
}
