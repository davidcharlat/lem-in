#ifndef PATHS_H
# define PATHS_H

# define NB_OF_PATHS 600000
# define NB_OF_TESTS 1000000

# include "../includes/struct.h"

void			copy_to_lop (t_test_paths *test, t_list_of_paths **ret);
int				test_new_path (t_sorttree *tree, t_neighbour *path);
void			clear_tree (t_sorttree *tree, t_neighbour *path, t_room *room);
t_list_of_paths	*test_paths (t_list_of_paths *lop, t_sorttree *tree, int nb);
t_tree_of_paths	*add_son_in_top (t_room *new_son, t_tree_of_paths *tree);
t_room			*find_room_in_po_sons (t_tree_of_paths *node, t_room *room);
t_tree_of_paths	*find_room_in_sons (t_tree_of_paths *node, t_room *room);
int 			add_1path	(t_list_of_paths **alist, t_tree_of_paths *leaf);
t_room			*find_next_room (int i, t_tree_of_paths *tree);
void			find_start (t_sorttree *tree, t_room **astart);
t_list_of_paths	*find_paths (t_room *start);
t_tree_of_paths	*fill_node_of_top (t_tree_of_paths **ato_fill, t_room *room,
					t_tree_of_paths *parent);

#endif

