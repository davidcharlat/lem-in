#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4000
# define BUFF_SIZE_GNL 1024
# define BOOL char

int				get_next_line_lemin(int const fd, char **line);
int				get_print_next_line(int const fd, char **line);

typedef struct		s_read
{
	int				size;
	int				index;
	int				fd;
	char			*read;
	struct s_read	*next;
}					t_read;

typedef struct		s_list_gnl
{
char				*content;
int					content_size;
BOOL				found;
struct s_list_gnl	*next;
}					t_list_gnl;

#endif

