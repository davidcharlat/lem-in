#ifndef VISUAL_H
# define VISUAL_H

# include "../includes/struct.h"
# include "../includes/visual_struct.h"
# include "../includes/visual_sdl.h"

# define NB_OF_STEP_FOR_ANT_TO_MOVE 100
# define WAITING_TIME 1
# define ROOM_WIDTH 10
# define ROOM_HEIGHT 10
# define ANT_WIDTH 9
# define ANT_HEIGHT 9
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define XCOORD nb_of_neighbour
# define YCOORD used

void	*sdlprint_room (t_sorttree *tree, void *ptr);
void	sdldraw_tunnel (t_room *r1, t_room *r2, void *ptr);
void 	make_ants_move (SDL_Window *window, t_sorttree *tree, char *line,
			t_room **ant_room_array, int max_coord[4], t_room *start_end[2], int nb_of_ants);
void	open_window (SDL_Window **awindow);
void	print_anthill (SDL_Window *window, t_sorttree *tree,
			t_room *start_end[2], int max_coord[4]);
t_room	**create_ant_room_array (int nb_of_ants, t_room *start);
int		is_move (char *line, t_sorttree *tree);
void	visual_get_nb_of_ants(char **aline, int *anb_of_ants);
void	visual_find_room (t_sorttree *tree, t_room **aroom, int status);
void	visual_get_tunnels(char **aline, t_sorttree **atree);
void	visual_get_rooms(char **aline, t_sorttree **atree, int (*max_coord)[4]);
int		get_next_line(int fd, char **line);

#endif

