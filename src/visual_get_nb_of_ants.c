#include <stdlib.h>
#include <unistd.h>
#include "../includes/get_next_line.h"
#include "../includes/exit.h"
#include "../includes/libft.h"

void	 visual_get_nb_of_ants(char **aline, int *anb_of_ants)
{
	get_next_line_lemin(0, aline);
	if (!(*aline))
			exit_msg ((char*)("ERROR"), 5);
	while ((*aline)[0] == '#')
	{
		free (*aline);
		get_next_line_lemin (0, aline);
		if (!(*aline))
			exit_msg ((char*)("ERROR"), 5);
	}
	(*anb_of_ants) = ft_atoi (*aline);
	if (*anb_of_ants < 0)
		exit_msg ((char*)("ERROR"), 5);
	if ((*anb_of_ants) == 0)
		exit_msg ((char*)("ERROR, no ant found"), 19);
	free (*aline);
}
