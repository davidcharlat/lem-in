#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/paths.h"
#include "../includes/exit.h"
#include "../includes/free.h"
	#include <stdio.h>
	
static void		put_ptr_to_next (t_sorttree *tree, t_test_paths **atest,
					t_list_of_paths **aptr)
{
	t_test_paths	*temp;
	
//temp = *atest;
//while (temp->next)
//{printf("put_ptr_to_next start: path starting with room %s\n", temp->lop->path->room->name);temp=temp->next;}
	temp = *atest;
	if ((*aptr)->next)
	{
		*aptr = (*aptr)->next;
//printf("ptr next\n");
		return;
	}
	if (!temp->next)
	{
		*aptr = NULL;
//printf("not ptr next\n");
		return;
	}
	while (temp->next->next)
		temp = temp->next;
	*aptr = temp->lop;
	clear_tree (tree, temp->lop->path, NULL);
//printf ("free %p\n", temp->next);
	free (temp->next);
	temp->next = NULL;
//temp = *atest;
//while (temp->next)
//{printf("put_ptr_to_next end: path starting with room %s\n", temp->lop->path->room->name);temp=temp->next;}
	put_ptr_to_next (tree, atest, aptr);
}

static void		add_path_to_test (t_test_paths *test, t_list_of_paths *path)
{
	t_test_paths	*temp;
	
//printf ("add path to test\n");
	temp = test;
	while (temp->next)
		temp = temp->next;
	if (temp->next = (t_test_paths*)malloc(sizeof(t_test_paths)))
	{
		temp->lop = path;
//printf ("path add: %p\n", path);
		temp->next->lop = NULL;
		temp->next->next = NULL;
	}
//temp = test;
//while (temp->next)
//{printf("path starting with room %s\n", temp->lop->path->room->name);temp=temp->next;}
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
		if (test_new_path (tree, path->path)) // renvoe 1 et rempli tree si ok, renvoye 0 et vide le tree inon
		{
//printf ("add1path will return 1\n");
			add_path_to_test (*atest, path);
//printf ("add1ath have added path and will return 1\n");
//printf ("add1path has returned 1\n");
			return (1);
		}
		put_ptr_to_next (tree, atest, aptr);
//printf ("add1path returned 0\n");
		return (0);
	}
//printf ("add1path returned -1\n");
	return (-1);
}

int				test_paths_combinat (t_sorttree *tree, t_test_paths **atest,
					t_list_of_paths **aptr, int antnb)
{
	t_test_paths	*temp;
	int				i;
	int				nb_of_paths;
//t_neighbour	*tn;

	
	i = 0;
	nb_of_paths = 0;
	while (!add_1path_and_test (tree, atest, aptr)); //add_1path_and_test returns 1 et add path if a new path is ok, returns 0 & don't add path' last past sinon  & augmente ptr
//printf ("new path found\n");
	temp = *atest;
	while (temp && temp->lop)
	{
//tn = temp->lop->path;
//printf("chemin %d ", nb_of_paths + 1);
//while (tn && tn->room)
//{printf ("%s ",tn->room->name); tn=tn->next;}
		i = i + temp->lop->lenght;
		nb_of_paths++;
		temp = temp->next;
	}
	if (!i)
		exit_msg ((char*)("ERROR no way out"), 16);	
	if (nb_of_paths)
//{
printf ("nb of paths: %d, i: %d, nb of steps:%d\n", nb_of_paths, i, ((antnb + i - 1) / nb_of_paths + 1));
		return (((antnb + i) - 1) / nb_of_paths + 1);
//}
	return (0);
}

t_list_of_paths	*test_paths (t_list_of_paths *lop, t_sorttree *tree, int antnb)
{
	t_list_of_paths	*ret;
	t_list_of_paths	*ptr;
	t_test_paths	*test;
	int				i;
	int				nb_of_step[2];
t_neighbour *nei;
	
	ret = NULL;
	test = NULL;
	i = 0;
	nb_of_step[1] = 2147483640;
	ptr = lop;
	while (i++ < NB_OF_TESTS && ptr)
	{
printf (" %d", i);
		nb_of_step[0] = test_paths_combinat (tree, &test, &ptr, antnb);
		if (nb_of_step[0] && nb_of_step[0] < nb_of_step[1])
		{
			nb_of_step[1] = nb_of_step[0];
			copy_to_lop (test, &ret); 				// void copy_to_lop (t_test *test, t_lop **ret), ret est null au début, prevoir malloc et free
		}
		if (ptr)
			put_ptr_to_next (tree, &test, &ptr);
	}
	free_test (test);
ptr = ret;
while (ptr && ptr->path){ nei = ptr->path;
printf ("new_path\n");
while (nei && nei->room){
printf ("%s - ", nei->room->name); nei = nei->next;}
printf ("     lenght: %d\n",ptr->lenght); ptr = ptr->next;}
	return (ret);
}
