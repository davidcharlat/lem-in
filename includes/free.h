#ifndef FREE_H
# define FREE_H

# include "../includes/struct.h"

void	free_lop (t_list_of_paths *lop, int free_neigh);
void	free_top (t_tree_of_paths *top);
void	free_neighbour(t_neighbour *neigh);
void	free_tree(t_sorttree *tree);
void	free_test (t_test_paths *test);

#endif

