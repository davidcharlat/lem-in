#ifndef STRUCT_H
# define STRUCT_H

# define BITTOSORT 4
/*
** number of bit to sort: 1, 2, 4, or 8
*/
# if BITTOSORT == 1
#  define NUMBEROFLEAVES 2
#  define LEAVESPERCHAR 8
# elif BITTOSORT == 2
#  define NUMBEROFLEAVES 4
#  define LEAVESPERCHAR 4
# elif BITTOSORT == 4
#  define NUMBEROFLEAVES 16
#  define LEAVESPERCHAR 2
# elif BITTOSORT == 8
#  define NUMBEROFLEAVES 256
#  define LEAVESPERCHAR 1
# endif

typedef struct				s_neighbour
{
	struct s_room			*room;
	struct s_neighbour		*next;
	struct s_neighbour		*prev;
}							t_neighbour;

typedef struct				s_room
{
	char					*name;
	int						used;
	int						status;
	int						nb_of_neighbour;
	struct s_neighbour		*neighbour;
}							t_room;

typedef struct				s_content
{
	char					*room_name;
	struct s_room			*sroom;
	int						name_size;
	int						sz;
}							t_content;

typedef struct				s_sorttree
{
	struct s_content		cont;
	int						level;
	struct s_sorttree		*next[NUMBEROFLEAVES];
}							t_sorttree;

typedef struct				s_tree_of_paths
{
	struct s_room			*room;
	struct s_tree_of_paths	*parent;
	struct s_po_sons_in_top	*possible_sons;
	struct s_sons_in_top	*sons;
	int						still_possible_son;
}							t_tree_of_paths;

typedef struct				s_po_sons_in_top
{
	struct s_room			*this_son;
	int						is_still_possible;
	struct s_po_sons_in_top	*next_son;
}							t_po_sons_in_top;

typedef struct				s_sons_in_top
{
	struct s_tree_of_paths	*this_son;
	int						is_still_possible;
	struct s_sons_in_top	*next_son;
}							t_sons_in_top;

typedef struct				s_list_of_paths
{
	struct s_neighbour		*path;
	int						lenght;
	struct s_list_of_paths	*next;
}							t_list_of_paths;

typedef struct				s_test_paths
{
	struct s_list_of_paths	*lop;
	struct s_test_paths		*next;
}							t_test_paths;

#endif

