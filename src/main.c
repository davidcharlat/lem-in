#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include "../includes/get.h"
#include "../includes/paths.h"
#include "../includes/struct.h"
#include "../includes/free.h"
#include "../includes/print.h"
		
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
	find_start (tree, &start);
	list_of_paths[0] = find_paths (start);
	list_of_paths[1] = test_paths (list_of_paths[0], tree, nb_of_ants);
	print_paths (list_of_paths[1], nb_of_ants);
	free_lop (list_of_paths[0], 1);
	free_lop (list_of_paths[1], 1);
	free_tree (tree);
	return (0);
}
