#include <stdlib.h>
#include <unistd.h>
#include "../includes/get_next_line.h"
#include "../includes/exit.h"
#include "../includes/libft.h"

void	get_nb_of_ants(char **aline, int *anb_of_ants)
{
	get_print_next_line (0, aline);
	if (!(write (1, "\n", 1)) || !(*aline))
			exit_msg ((char*)("ERROR"), 5);
	while ((*aline)[0] == '#')
	{
		free (*aline);
		get_print_next_line (0, aline);
		if (!(write (1, "\n", 1)) || !(*aline))
			exit_msg ((char*)("ERROR"), 5);
	}
	(*anb_of_ants) = ft_atoi (*aline);
	if (*anb_of_ants < 0)
		exit_msg ((char*)("ERROR"), 5);
	if ((*anb_of_ants) == 0)
		exit_msg ((char*)("ERROR, no ant found"), 19);
	free (*aline);
}
