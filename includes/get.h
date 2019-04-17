#ifndef GET_H
# define GET_H

# include "../includes/struct.h"

int			is_room (char *line);
int			is_comment (char *line);
int			is_start_end (char *line);
int			is_tunnel (char *line, t_sorttree *tree);
void		get_nb_of_ants(char **aline, int *anb_of_ants);
void		get_rooms(char **aline, t_sorttree **atree);
void		get_tunnels(char **aline, t_sorttree **atree);
t_room		*find_room (t_sorttree *root, char *line, int line_len);
t_sorttree	*streenew (t_content cont);
void		streeins (t_sorttree *root, t_sorttree *node);
int			split (char *content, int cnt_size, int n);
void		sort_room_like_hotrace (t_room *this_room, t_sorttree *tree);
t_sorttree	*new_sorttree (void);

#endif

