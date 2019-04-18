#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/exit.h"
#include "../includes/free.h"
	
static void		put_ptr_to_next (t_sorttree *tree, t_test_paths **atest,
					t_list_of_paths **aptr)
{
	t_test_paths	*temp;
	
	temp = *atest;
	if ((*aptr)->next)
	{
		*aptr = (*aptr)->next;
		return;
	}
	if (!temp->next)
	{
		*aptr = NULL;
		return;
	}
	while (temp->next->next)
		temp = temp->next;
	*aptr = temp->lop;
	clear_tree (tree, temp->lop->path, NULL);
	free (temp->next);
	temp->next = NULL;
	put_ptr_to_next (tree, atest, aptr);
}

static void		add_path_to_test (t_test_paths *test, t_list_of_paths *path)
{
	t_test_paths	*temp;
	
	temp = test;
	while (temp->next)
		temp = temp->next;
	if ((temp->next = (t_test_paths*)malloc(sizeof(t_test_paths))))
	{
		temp->lop = path;
		temp->next->lop = NULL;
		temp->next->next = NULL;
	}
}

int				add_1path_and_test (t_sorttree *tree, t_test_paths **atest,
					t_list_of_paths **aptr)
{
	t_list_of_paths	*path;
	
	if (!(*atest))
	{
		if (!(*atest = (t_test_paths*)malloc(sizeof(t_test_paths))))
			exit_msg ((char*)("ERROR"), 5);
		(*atest)->lop = NULL;
		(*atest)->next = NULL;
	}
	if (*aptr)
	{
		path = (*aptr);
		if (test_new_path (tree, path->path))
		{
			add_path_to_test (*atest, path);
			return (1);
		}
		put_ptr_to_next (tree, atest, aptr);
		return (0);
	}
	return (-1);
}

int				test_paths_combinat (t_sorttree *tree, t_test_paths **atest,
					t_list_of_paths **aptr, int antnb)
{
	t_test_paths	*temp;
	int				i;
	int				nb_of_paths;
	
	i = 0;
	nb_of_paths = 0;
	while (!add_1path_and_test (tree, atest, aptr));
	temp = *atest;
	while (temp && temp->lop)
	{
		i = i + temp->lop->lenght;
		nb_of_paths++;
		temp = temp->next;
	}
	if (!i)
		exit_msg ((char*)("ERROR no way out"), 16);	
	if (nb_of_paths)
		return (((antnb + i) - 1) / nb_of_paths + 1);
	return (0);
}

t_list_of_paths	*test_paths (t_list_of_paths *lop, t_sorttree *tree, int antnb)
{
	t_list_of_paths	*ret;
	t_list_of_paths	*ptr;
	t_test_paths	*test;
	int				i;
	int				nb_of_step[2];
	
	ret = NULL;
	test = NULL;
	i = 0;
	nb_of_step[1] = 2147483640;
	ptr = lop;
	while (i++ < NB_OF_TESTS && ptr)
	{
		nb_of_step[0] = test_paths_combinat (tree, &test, &ptr, antnb);
		if (nb_of_step[0] && nb_of_step[0] < nb_of_step[1])
		{
			nb_of_step[1] = nb_of_step[0];
			copy_to_lop (test, &ret);
		}
		if (ptr)
			put_ptr_to_next (tree, &test, &ptr);
	}
	free_test (test);
	return (ret);
}
