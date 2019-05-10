#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include "../includes/get.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/visual.h"
#include "../includes/visual_struct.h"
#include "../includes/visual_sdl.h"
#include "../includes/libft.h"

void	visu_hex (char **aline, int max_coord[4], t_sorttree *tree, int antnb)
{
	t_room		*start_end[2];
	t_room		**ant_room_array;
	SDL_Surface	*window;
	SDL_Event	event;
	char		key;
	int			gnl;

	gnl = ft_strlen(*aline);
	key = 1;
	visual_find_room (tree, &(start_end[0]), 1);
	visual_find_room (tree, &(start_end[1]), 2);
	ant_room_array = create_ant_room_array (antnb, start_end[1]);
	open_window (&window);
	print_anthill (window, tree, start_end, max_coord);
	while (key && gnl > 0)
	{
		SDL_WaitEvent(&event);
		key = 1;
		if (event.type == SDL_QUIT)
			key = 0;
		if (event.type == SDL_KEYDOWN)
		{
			make_ants_move (window, tree, *aline, ant_room_array, max_coord, start_end, antnb);
			free (*aline);
			gnl = get_next_line_lemin (0, aline);
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
	free_tree (tree);
	return (0);
}
