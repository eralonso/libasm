#include "tests/list_at.h"

void	__test_list_at_time(
		t_list *(*list_at_pointer)(t_list *, unsigned int), char *name, t_list *begin_list, unsigned int nbr)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*ret;

	print_list(begin_list);
	start = get_time();
	ret = list_at_pointer(begin_list, nbr);
	end = get_time();
	printf("\n%s(%p, %u) == %p  in %lu microseconds\n", name, begin_list, nbr, ret, end - start);
	printf("\n");
	return ;
}

void	test_list_at(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 9};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_AT\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_at_time(ft_list_at, "\tft_list_at", begin_list, position[i]);
	}
	clear_list(begin_list);
	return ;
}
