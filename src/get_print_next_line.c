#include <stdlib.h>
#include <unistd.h>
#include "../includes/get_next_line.h"

static t_read		*ft_freeread(t_read *red, t_read *prev, t_read **start)
{
	if (!prev)
		*start = red->next;
	else
		prev->next = red->next;
	free(red->read);
	free(red);
	if (!prev)
		return (*start);
	else
		return (prev->next);
}

static t_read		*ft_newread(int fd)
{
	t_read			*red;
	void			*tmp;
	int				ret;

	if (!(red = (t_read *)malloc(sizeof(t_read))))
		return (NULL);
	if (!(tmp = malloc(sizeof(char) * BUFF_SIZE)))
	{
		free(red);
		return (NULL);
	}
	if ((ret = read(fd, tmp, BUFF_SIZE)) < 0)
	{
		free(red);
		free(tmp);
		return (NULL);
	}
	red->read = (char *)tmp;
	red->fd = fd;
	red->size = ret;
	red->next = NULL;
	red->index = 0;
	return (red);
}

static int			ft_print(int n, t_read **tab, t_read **s, char **l)
{
	char			*tmpstr;
	int				index;

	if (!tab[0] || n < 0 || !(tmpstr = (char *)malloc(sizeof(char) * (n + 1))))
		return (-1);
	index = (tab[0])->index;
	if (n == 0)
		tab[0] = ft_freeread(tab[0], tab[1], s);
	*l = tmpstr;
	while (n--)
	{
		*tmpstr++ = (tab[0])->read[index++];
		if (index == (tab[0])->size)
		{
			tab[0] = ft_freeread(tab[0], tab[1], s);
			index = 0;
		}
	}
	*tmpstr = 0;
	if (!tab[0] || (index == tab[0]->size && tab[0]->size < BUFF_SIZE))
		return (0);
	tab[0]->index = index + 1;
	if (tab[0]->index == tab[0]->size)
		tab[0] = ft_freeread(tab[0], tab[1], s);
	return (1);
}

static int			ft_findendl(int fd, t_read *red)
{
	int				index;
	int				size;
	t_read			*tmplst;

	size = 0;
	index = red->index;
	while (red->read[index] != '\n' && index < red->size)
	{
		index++;
		size++;
		if (index == red->size && red->size == BUFF_SIZE)
		{
			if (!(tmplst = ft_newread(fd)))
				return (-1);
			tmplst->next = red->next;
			red->next = tmplst;
			red = tmplst;
			index = 0;
		}
	}
	return (size);
}

int					get_print_next_line(int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			*tab[4];
	int				temp[2];

	tab[3] = NULL;
	if (!start)
		start = ft_newread(fd);
	if (!(tab[2] = start))
		return (-1);
	while ((tab[2])->fd != fd)
	{
		if (!((tab[2])->next))
			(tab[2])->next = ft_newread(fd);
		(tab[3]) = (tab[2]);
		(tab[2]) = (tab[2])->next;
	}
	if (!(tab[2]) || !start)
		return (-1);
	tab[0] = (tab[2]);
	tab[1] = (tab[3]);
	temp[0] = ft_findendl(fd, tab[2]);
	temp[1] = (ft_print(temp[0], tab, &start, line));
	write (1, *line, temp[0]);
	write (1, "\n", 1);
	return (temp[1]);	
}
