#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/libft.h"
#include "../includes/get.h"
#include "../includes/exit.h"
#include "../includes/visual_sdl.h"
#include "../includes/visual.h"

static void	sdldraw_ants (SDL_Surface *window, t_room **ant_room_array, int max_coord[4], int nb_of_ants)
{
	SDL_Surface	*sdlant;
	SDL_Rect	position;
	
	if (!(sdlant = SDL_CreateRGBSurface(SDL_HWSURFACE, ANT_HEIGHT, ANT_WIDTH, 32, 0, 0, 0, 0)))
		exit_msg ((char*)("error SDL_creatergb"), 19);
	SDL_FillRect (sdlant, NULL, SDL_MapRGB(window->format, 0, 127, 255));
	while (nb_of_ants)
	{
		position.x = ((ant_room_array[nb_of_ants]->XCOORD) - max_coord[0]) * (WIN_WIDTH - ANT_WIDTH) / (max_coord[1] - max_coord[0]);
		position.y = ((ant_room_array[nb_of_ants]->YCOORD) - max_coord[2]) * (WIN_HEIGHT- ANT_HEIGHT) / (max_coord[3] - max_coord[2]);
		nb_of_ants--;
		SDL_BlitSurface(sdlant, NULL, window, &position);
	}
	SDL_Flip (window);
	SDL_FreeSurface(sdlant);
}

static void	draw_ant_moving (t_room *prevroom, t_room *room,
				SDL_Surface *window, int max_coord[4],
				t_sorttree *tree)
{
	SDL_Surface	*sdlant;
	SDL_Rect	position;
	int			c[5];
	void		*ptr[2];
	
	ptr[0] = (void*)(window);
	ptr[1] = (void*)(max_coord);
	c[0] = ((prevroom->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]) + (ROOM_WIDTH - ANT_WIDTH)/ 2;
	c[1] = ((prevroom->YCOORD) - max_coord[2]) * (WIN_HEIGHT - ROOM_HEIGHT) / (max_coord[3] - max_coord[2]) + (ROOM_HEIGHT - ANT_HEIGHT) / 2;
	c[2] = ((room->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]) + (ROOM_WIDTH - ANT_WIDTH) / 2;
	c[3] = ((room->YCOORD) - max_coord[2]) * (WIN_HEIGHT - ROOM_HEIGHT) / (max_coord[3] - max_coord[2]) + (ROOM_HEIGHT - ANT_HEIGHT) / 2;
	c[4] = NB_OF_STEP_FOR_ANT_TO_MOVE;
	if (!(sdlant = SDL_CreateRGBSurface(SDL_HWSURFACE, ANT_HEIGHT, ANT_WIDTH, 32, 0, 0, 0, 0)))
		exit_msg ((char*)("error SDL_creatergb"), 19);
	if (!room || !prevroom)
		exit_msg ((char*)("ERROR"), 5);
	while (c[4]--)
	{
		if (c[4] < NB_OF_STEP_FOR_ANT_TO_MOVE - 1)
			SDL_FillRect (sdlant, NULL, SDL_MapRGB(window->format, 0, 0, 0));
		else
			SDL_FillRect (sdlant, NULL, SDL_MapRGB(window->format, 195, 195, 195));
		position.x = c[2] + (c[4] + 1) * (c[0] - c[2]) / NB_OF_STEP_FOR_ANT_TO_MOVE;
		position.y = c[3] + (c[4] + 1) * (c[1] - c[3]) / NB_OF_STEP_FOR_ANT_TO_MOVE;
		SDL_BlitSurface(sdlant, NULL, window, &position);
		SDL_FillRect (sdlant, NULL, SDL_MapRGB(window->format, 0, 127, 255));
		position.x = c[2] + c[4] * (c[0] - c[2]) / NB_OF_STEP_FOR_ANT_TO_MOVE;
		position.y = c[3] + c[4] * (c[1] - c[3]) / NB_OF_STEP_FOR_ANT_TO_MOVE;
		SDL_BlitSurface(sdlant, NULL, window, &position);
		SDL_Flip (window);
		SDL_Delay (WAITING_TIME);
	}
	sdldraw_tunnel (prevroom, room, ptr);
	sdlprint_room (tree, ptr);
	SDL_Flip (window);
	SDL_FreeSurface(sdlant);
}

t_room		*find_antroom (t_sorttree *tree, char *line, int cursor)
{
	int		curs2;
	char	tempchar;
	t_room	*ret;
	
	while (line[cursor] && line[cursor] != '-')
		(cursor)++;
	curs2 = (cursor) + 1;
	while (line[cursor] && line[cursor] != 'L' && line[(cursor) - 1] != ' ')
		(cursor)++;
	if (line[cursor])
		(cursor)--;
	tempchar = line[cursor];
	line[cursor] = 0;
	ret = find_room (tree, line + curs2, cursor - curs2);
	line[cursor] = tempchar;
	return (ret);
}

void 	make_ants_move (SDL_Surface *window, t_sorttree *tree, char *line,
			t_room **ant_room_array, int max_coord[4], t_room *start_end[2], int nb_of_ants)
{
	int		i;
	int		antnum;
	t_room	*room;
	t_room	*prevroom;
	
	i = ft_strlen(line);
	while (i && line[i - 1] == ' ')
	{
		line[i - 1] = 0;
		i--;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == 'L' && (!i || line[i - 1] == ' '))
		{
			antnum = ft_atoi (line + i + 1);
			room = find_antroom (tree, line, i);
			prevroom = (ant_room_array)[antnum];
			if (!room || !prevroom)
				exit_msg ((char*)("ERROR"), 5);
			(ant_room_array)[antnum] = room;
			draw_ant_moving (prevroom, room, window, max_coord, tree);
			sdldraw_ants (window, ant_room_array, max_coord, nb_of_ants);
		}
		i++;
	}
	print_anthill (window, tree, start_end, max_coord);
	sdldraw_ants (window, ant_room_array, max_coord, nb_of_ants);
}
