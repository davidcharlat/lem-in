#include "../includes/struct.h"
#include "../includes/libft.h"
#include <stdlib.h>

t_sorttree	*streenew (t_content cont)
{
	int			i;
	t_sorttree	*temp;

	i = -1;
	temp = (t_sorttree*)malloc(sizeof(t_sorttree));
	if (!temp)
		return (NULL);
	temp->cont = cont;
	temp->level = 0;
	while (i++ < NUMBEROFLEAVES - 1)
		temp->next[i] = NULL;
	return (temp);
}

t_sorttree	*new_sorttree (void)
{
	t_content	cont;
	
	cont.room_name = NULL;
	cont.name_size = 0;
	cont.sroom = NULL;
	cont.sz = 0;
	return (streenew (cont));
}

int			split (char *content, int cnt_size, int n)
{
	int	place;
	
	if ((n) > LEAVESPERCHAR * cnt_size)
		return (-1);
	place = (n % LEAVESPERCHAR) * BITTOSORT;
	return ((int)(((int)(content[n / LEAVESPERCHAR])>>place)
		& (NUMBEROFLEAVES - 1)));
}

void		streeins (t_sorttree *root, t_sorttree *node)
{
	t_content	temp;
	int			nxt;

	if (node)
	{
		node->level = root->level;
		nxt = split((node->cont).room_name, (node->cont).name_size, node->level);
		if (root->next[nxt] == NULL)
		{
			root->next[nxt] = node;
			(node->level)++;
		}
		else
		{
			if ((root->next[nxt]->cont).name_size > (node->cont).name_size)
			{
				temp = (node->cont);
				node->cont = root->next[nxt]->cont;
				root->next[nxt]->cont = temp;
			}
			if (root->level < LEAVESPERCHAR * (node->cont).name_size)
				streeins (root->next[nxt], node);
		}
	}
}

void		sort_room_like_hotrace (t_room *this_room, t_sorttree *tree)
{
	t_content			cont;
	
	cont.room_name = this_room->name;
	cont.name_size = ft_strlen (this_room->name);
	cont.sroom = this_room;
	cont.sz = 0;
	streeins (tree, streenew (cont));
}
