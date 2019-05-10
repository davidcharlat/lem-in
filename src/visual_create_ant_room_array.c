#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/exit.h"
	#include <stdio.h>

t_room	**create_ant_room_array (int nb_of_ants, t_room *start)
{
	t_room	**temp;
	if (!(temp = (t_room**)malloc (sizeof(t_room*) * (nb_of_ants + 1))))
		exit_msg ((char*)("ERROR"), 5);
	while (nb_of_ants + 1)
		*(temp + --nb_of_ants + 1) = start;
	return (temp);
}
