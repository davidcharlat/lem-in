#include <stdlib.h>
#include <unistd.h>
#include "../includes/struct.h"
#include "../includes/get.h"
#include "../includes/free.h"

void	copy_to_lop (t_test_paths *test, t_list_of_paths **ret)
{
	t_test_paths	*cpyt;
	t_list_of_paths *tlop;

	cpyt = test;
	tlop = *ret;
	if (!(*ret = (t_list_of_paths*)malloc(sizeof(t_list_of_paths))))
		return;
	free_lop (tlop, 0);
	tlop = *ret;
	while (cpyt && cpyt->lop)
	{
		tlop->path = cpyt->lop->path;
		tlop->lenght = cpyt->lop->lenght;
		if (!(tlop->next = (t_list_of_paths*)malloc(sizeof(t_list_of_paths))))
			return;
		tlop = tlop->next;
		cpyt = cpyt->next;
	}
	tlop->path = NULL;
	tlop->lenght = 0;
	tlop->next = NULL;
}
