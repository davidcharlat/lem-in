#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/visual_struct.h"
#include "../includes/exit.h"
	#include <stdio.h>

static void	put_find_room (t_sorttree *tree, t_room **astart, int sts)
{
	int i;
	
	i = -1;
	if (tree)
	{
		if (((tree->cont).sroom) && ((tree->cont).sroom)->status == sts)
		{
			*astart = ((tree->cont).sroom);
			return;
		}
		while (i++ < NUMBEROFLEAVES - 1)
		{
			if (tree->next[i])
				put_find_room (tree->next[i], astart, sts);
		}
		if (tree->level == 0)
			return;
	}
}

void		visual_find_room (t_sorttree *tree,
				t_room **aroom, int status)
{
	*aroom = NULL;
printf ("visual find room\n");
	put_find_room (tree, aroom, status);
	if (!(*aroom))	
		exit_msg ((char*)("ERROR"), 5);
}
