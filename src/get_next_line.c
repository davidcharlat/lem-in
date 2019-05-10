#include <stdlib.h>
#include <unistd.h>
#include "../includes/exit.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
	#include<stdio.h>

static void	end_of_fct_export (t_list_gnl **root, char *newline, int done, int todo)
{
	int		todocpy;
	BOOL	found;
	
	found = 0;
	todocpy = todo;
	if (!*root || !newline)
		return;
	newline[done + todo] = 0;
	while (todo--)
		newline[done + todo] = ((*root)->content)[todo];
	while (((*root)->content_size) > 2 + todocpy + todo++)
	{
		((*root)->content)[todo] = ((*root)->content)[todo + todocpy + 1];
		if (((*root)->content)[todo] == '\n')
			found = 1;
	}
	(*root)->content_size -= todocpy + 1;
	(*root)->found = found;
}

static void	export_line (t_list_gnl **root, char **line)
{
	char	*newline;
	t_list_gnl	*rootcpy;
	int		i[4] = {0};
	
	rootcpy = *root;
	while (rootcpy && rootcpy->found == 0)
	{
		i[0] = i[0] + rootcpy->content_size;
		rootcpy = rootcpy->next;
	}
	while (rootcpy && (rootcpy->content)[i[1]] != '\n')
		i[1]++;
	newline = (char*)malloc(i[0] + i[1] + 2);
	while (*root && (*root)->found == 0 && newline)
	{
		i[2] = 0;
		while (((*root)->content_size) > i[2])
			newline[i[3]++] = ((*root)->content)[i[2]++];
		rootcpy = *root;
		*root = (*root)->next;
		free (rootcpy->content);
		free (rootcpy);
	}
	*line = newline;
	end_of_fct_export (root, newline, i[3], i[1]);
}

static void	ft_lst_newadd_back (t_list_gnl **root, char *data, int size, BOOL found)
{
	t_list_gnl	*vrootcpy;
	
	vrootcpy = *root;
	if (vrootcpy)
	{
		while (vrootcpy->next)
			vrootcpy = vrootcpy->next;
		vrootcpy->next = (t_list_gnl*)malloc(sizeof(t_list_gnl));
		if (!vrootcpy->next)
			return;
		vrootcpy->next->content = data;
		vrootcpy->next->content_size = size;
		vrootcpy->next->found = found;
		vrootcpy->next->next = NULL;
	}
	else
	{
		*root = (t_list_gnl*)malloc(sizeof(t_list_gnl));
		if (!root)
			return;
		(*root)->content = data;
		(*root)->content_size = size;
		(*root)->found = found;
		(*root)->next = NULL;
	}
}

static int	get_line (const int fd, t_list_gnl **atext, char **line)
{
	char	buff[BUFF_SIZE_GNL];
	int		ret;
	BOOL	found;
	char	*temp;
	int		retcpy;
	
	found = 0;
	ret = 0;
	while (!found && (ret = read (fd, buff, BUFF_SIZE_GNL)) > 0)
	{
		retcpy = ret;
		if (!(temp = (char*)malloc(BUFF_SIZE_GNL + 1)))
			return (-1);
		while (ret--)
		{
			temp[ret] = buff[ret];
			if (temp[ret] == '\n')
				found = 1;
		}
		ft_lst_newadd_back (atext, temp, retcpy, found);
	}
	export_line (atext, line);
	if (!*line)
		return (-1);
	return (found);
}

int		get_next_line_lemin (const int fd, char **line)
{
	static t_list_gnl	*text = NULL;
	int				i;

	if (text)
	{
		i = 0;
		while (i < text->content_size)
		{
			if ((text->content)[i] == '\n')
			{
				export_line (&text, line);
				return (1);
			}
			i++;
		}
	}
	return (get_line (fd, &text, line));
}
