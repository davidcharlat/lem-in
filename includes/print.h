#ifndef PRINT_H
# define PRINT_H

# include "../includes/struct.h"

void	print_paths (t_list_of_paths *lop, int nb_of_ants);
void	browse_lop (t_list_of_paths *lop, void *ptr,
	void*(*f)(t_list_of_paths*, void*));
void	browse_nei (t_neighbour *nei, void *p, void*(*f)(t_neighbour*, void*));
void	*set_used_in_lop_rooms (t_list_of_paths *lop, void *nb);
void	*set_used_in_nei_rooms (t_neighbour *nei, void *nb);
void	*set_prev_in_nei_of_lop (t_list_of_paths *lop, void *nb);

#endif

