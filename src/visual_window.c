#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/print.h"
#include "../includes/visual.h"
#include "../includes/visual_sdl.h"
	#include <stdio.h>
	
void	sdldraw_tunnel (t_room *r1, t_room *r2, void *ptr)
{
	int			*max_coord;
	int			c[6];
	SDL_Surface	*window;
	SDL_Surface	*sdltunnel;
	SDL_Rect	position;
		
	window = (SDL_Surface*)(((void**)ptr)[0]);
	max_coord = (int*)(((void**)ptr)[1]);
	c[0] = WIN_WIDTH + WIN_HEIGHT - ROOM_WIDTH / 2 - ROOM_HEIGHT / 2;
	c[1] = ((r1->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]) + ROOM_WIDTH / 2;
	c[2] = ((r1->YCOORD) - max_coord[2]) * (WIN_HEIGHT - ROOM_HEIGHT) / (max_coord[3] - max_coord[2]) + ROOM_HEIGHT / 2;
	c[3] = ((r2->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]) + ROOM_WIDTH / 2;
	c[4] = ((r2->YCOORD) - max_coord[2]) * (WIN_HEIGHT - ROOM_HEIGHT) / (max_coord[3] - max_coord[2]) + ROOM_HEIGHT / 2;
	c[5] = c[0];
	if (!(sdltunnel = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0)))
	{
		fprintf (stderr, "SDL_creatergb");
		exit (EXIT_FAILURE);
	}
//printf ("broswe tree:  tunnel from %s to %s \n", r1->name, r2->name );
	SDL_FillRect (sdltunnel, NULL, SDL_MapRGB(window->format, 31, 31, 31));
	while (c[0]--)
	{
		position.x = c[1] + c[0] * (c[3] - c[1]) / c[5];
		position.y = c[2] + c[0] * (c[4] - c[2]) / c[5];
		SDL_BlitSurface(sdltunnel, NULL, window, &position);
	}
	SDL_FreeSurface(sdltunnel);
}

void	*sdlprint_tunnel (t_sorttree *tree, void *ptr)
{
	
	t_neighbour	*nei;
		
	if ((tree->cont).sroom && (tree->cont).sroom->neighbour)
	{
		nei = (tree->cont).sroom->neighbour;
		while (nei)
		{
			sdldraw_tunnel ((tree->cont).sroom, nei->room, ptr);
			nei = nei->next;
		}
	}
	return ((void*)tree);
}

void	*sdlprint_room (t_sorttree *tree, void *ptr)
{
	int			*max_coord;
	SDL_Surface	*window;
	SDL_Surface	*sdlroom;
	SDL_Rect	position;
	
	window = (SDL_Surface*)(((void**)ptr)[0]);
	max_coord = (int*)(((void**)ptr)[1]);
	if (!(sdlroom = SDL_CreateRGBSurface(SDL_HWSURFACE, ROOM_HEIGHT, ROOM_WIDTH, 32, 0, 0, 0, 0)))
	{
		fprintf (stderr, "SDL_creatergb");
		exit (EXIT_FAILURE);
	}
	if (tree && (tree->cont).sroom)
	{
//printf ("broswe tree: room %s\n", (tree->cont).sroom->name);
		SDL_FillRect (sdlroom, NULL, SDL_MapRGB(window->format, 195, 195, 195));
		position.x = (((tree->cont).sroom->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]);
		position.y = (((tree->cont).sroom->YCOORD) - max_coord[2]) * (WIN_HEIGHT- ROOM_HEIGHT) / (max_coord[3] - max_coord[2]);
		SDL_BlitSurface(sdlroom, NULL, window, &position);
	}
	SDL_FreeSurface(sdlroom);
	return ((void*)tree);
}

void	open_window (SDL_Surface **awindow)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	}
	SDL_EnableKeyRepeat(50, 50);
	if(!((*awindow) = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)))
	{
		fprintf(stderr, "SDL_SetVideoMode error");
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("Lem_in visual, press any key to make ants move", NULL);
}

void	print_anthill (SDL_Surface *window, t_sorttree *tree, t_room *start_end[2], int max_coord[4]) //affiche les couloir et les salles dans window
{
	SDL_Surface	*sdlroom;
	SDL_Rect	position;
	void		*ptr[2];
	
	if(!(sdlroom = SDL_CreateRGBSurface(SDL_HWSURFACE, ROOM_HEIGHT, ROOM_WIDTH, 32, 0, 0, 0, 0)))
	{
		fprintf (stderr, "SDL_creatergb");
		exit (EXIT_FAILURE);
	}
	ptr[0] = (void*)(window);
	ptr[1] = (void*)(max_coord);
	browse_tree (tree, (void*)(ptr), &sdlprint_tunnel);
	browse_tree (tree, (void*)(ptr), &sdlprint_room);
	SDL_FillRect (sdlroom, NULL, SDL_MapRGB(window->format, 0, 255, 0));
	position.x = ((start_end[0]->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]);
	position.y = ((start_end[0]->YCOORD) - max_coord[2]) * (WIN_HEIGHT- ROOM_HEIGHT) / (max_coord[3] - max_coord[2]);
printf ("room 0: %s x:%d, y:%d\n", start_end[0]->name, position.x, position.y);
	SDL_BlitSurface(sdlroom, NULL, window, &position);
	SDL_FillRect (sdlroom, NULL, SDL_MapRGB(window->format, 255, 0, 0));
	position.x = ((start_end[1]->XCOORD) - max_coord[0]) * (WIN_WIDTH - ROOM_WIDTH) / (max_coord[1] - max_coord[0]);
	position.y = ((start_end[1]->YCOORD) - max_coord[2]) * (WIN_HEIGHT- ROOM_HEIGHT) / (max_coord[3] - max_coord[2]);
printf ("room 0: %s x:%d, y:%d\n", start_end[1]->name, position.x, position.y);
	SDL_BlitSurface(sdlroom, NULL, window, &position);
	SDL_Flip (window);
	SDL_FreeSurface(sdlroom);
}
