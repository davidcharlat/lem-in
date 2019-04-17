#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include "../includes/get.h"
#include "../includes/paths.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/print.h"
		#include <stdio.h>
		
int	main(void)
{
	char				*line;
	int					nb_of_ants;
	t_sorttree			*tree;
	t_room				*start;
	t_list_of_paths		*list_of_paths[2];

	get_nb_of_ants (&line, &nb_of_ants);
	get_rooms (&line, &tree);
	get_tunnels (&line, &tree);
	find_start (tree, &start); //find_start
printf ("room end: %s\n", (start)->name);
	list_of_paths[0] = find_paths (start);//find_paths
	list_of_paths[1] = test_paths (list_of_paths[0], tree, nb_of_ants);
	print_paths (list_of_paths[1], tree, nb_of_ants);//print_paths
	free_lop (list_of_paths[0], 1);
	free_lop (list_of_paths[1], 1);
	free_tree (tree);
//printf ("%d\n", sizeof(t_list_of_paths));
	return (0);
}	
/*		
	
#include "../includes/classify_lines.h"
#include "../includes/add_room.h"
#include "../includes/add_tunnel.h"
#include "../includes/sorttree.h"
#include "../includes/free.h"
#include "../includes/find_paths.h"
	#include <stdio.h>
	
int	main(void)
{
	char				*line;
	int					ant_nb;
	t_sorttree			*tree;
	t_content			cont;
	t_room				*start;
	t_list_of_paths		*list_of_paths;
	
	line = NULL;
	cont.room_name = NULL;
	cont.name_size = 0;
	cont.data = NULL;
	cont.sz = 0;
	tree = streenew (cont);

	
		add_room (&line, tree);
	if (line_is_tunnel (line, tree))
		add_tunnel (&line, tree);
	while (get_next_line (0, &line) && line_is_tunnel (line, tree))
		add_tunnel (&line, tree);
	free (line);
	while (get_next_line (0, &line)) // these line and 2 next to free struct of gnl
		free (line);
	free (line);
	start = find_start (tree);
if (start)
printf ("room start: %s\n", (start)->name);
else
printf ("start not found\n");
	list_of_paths = find_paths (tree, start); //
	
	free_tree (tree);
	return (0);
}

//tofree: each t_room, each t_room->name



*/
