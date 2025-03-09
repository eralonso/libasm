#include "tests/list_size.h"

void	__test_list_size_time(
		int (*list_size_pointer)(t_list *), char *name, t_list *begin_list)
{
	unsigned long	start;
	unsigned long	end;
	int				size;

	start = get_time();
	size = list_size_pointer(begin_list);
	end = get_time();
	printf("%s(%p) == %i in %lu microseconds\n", name, begin_list, size, end - start);
	printf("\n");
	return ;
}

void	test_list_size(void)
{
	void	*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	t_list	*begin_list = NULL;

	printf("TEST: LIST_SIZE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_size_time(ft_list_size, "\tft_list_size", begin_list);
		ft_list_push_front(&begin_list, strs[i]);
	}
	clear_list(begin_list);
	return ;
}
