#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/get.h"

static int		ft_unendedstr2cmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1024);
	if (!s2)
		return (1023);
	while (*(s1) && *(s1) == *(s2))
	{
		s1++;
		s2++;
	}
	return ((int)*(s1));
}

t_room		*find_room (t_sorttree *root, char *line, int line_len)
{
	int nextletter;
		
	while (root && line_len > (root->cont).name_size )
	{
		nextletter = split (line, line_len, root->level);
		root = root->next[nextletter];
	}
	while (root && ft_unendedstr2cmp (line, (root->cont).room_name) 
		&& line_len == (root->cont).name_size)
	{
		nextletter = split(line, line_len, root->level);
		root = root->next[nextletter];
	}
	if (root && line_len == (root->cont).name_size 
		&& !ft_unendedstr2cmp (line, (root->cont).room_name))
		return ((root->cont).sroom);
	return (NULL);
}
