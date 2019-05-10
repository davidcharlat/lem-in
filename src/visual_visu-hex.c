#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/visual.h"
#include "../includes/visual_struct.h"
#include "../includes/visual_sdl.h"
#include "../includes/libft.h"
	#include <stdio.h>
		

void	visu_hex (char **aline, int max_coord[4], t_sorttree *tree, int antnb)
{
	t_room		*start_end[2];
	t_room		**ant_room_array;
	SDL_Surface	*window;
	SDL_Event	event;
	char		key;
	int			gnl;
int i = 0;

	gnl = ft_strlen(*aline);
	key = 1;
	visual_find_room (tree, &(start_end[0]), 1);
	visual_find_room (tree, &(start_end[1]), 2);
printf ("roomend:%s, %d, %d, room start:%s, %d, %d\n", start_end[0]->name, start_end[0]->XCOORD, start_end[0]->YCOORD, start_end[1]->name, start_end[1]->XCOORD, start_end[1]->YCOORD);
	ant_room_array = create_ant_room_array (antnb, start_end[1]);
while (i < antnb){printf("ant %d in room %s\n", i+1, (*(ant_room_array + i))->name ); i++;}
	open_window (&window);
	print_anthill (window, tree, start_end, max_coord);
printf ("line freed, new line lenght: %d\n", ft_strlen (*aline));
	while (key && gnl > 0)
	{
		SDL_WaitEvent(&event);
		key = 1;
		if (event.type == SDL_QUIT)
			key = 0;
		if (event.type == SDL_KEYDOWN)
		{
			make_ants_move (window, tree, *aline, ant_room_array, max_coord, start_end, antnb); //void make_ants_move (SDL_Surface *window, t_sorttree *tree, char *line, void *ant_room_array)
printf ("new line: %s\n", *aline);
			free (*aline);
			gnl = get_next_line_lemin (0, aline);
printf ("line freed, new line lenght: %d\n", ft_strlen (*aline));
		}
	}
	free (*aline);
}

int		main(void)
{
	char		*line;
	int			nb_of_ants;
	int			max_coo[4] = {2147483647, 2147483647, 2147483647, 2147483647};
	t_sorttree	*tree;

	visual_get_nb_of_ants (&line, &nb_of_ants);
	visual_get_rooms (&line, &tree, &max_coo);
	visual_get_tunnels (&line, &tree);
	visu_hex (&line, max_coo, tree, nb_of_ants); 
// &line pour saisir les mvts, max_coo pour réétablir les coord, tree pour placer les salle aisnsi que start end 
	free_tree (tree);
	return (0);
}
