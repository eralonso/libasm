#include "tests/list_index.h"

void	__test_list_index_time(
		int (*list_index_pointer)(t_list *, t_list *), char *name, t_list *begin_list, t_list *node)
{
	unsigned long	start;
	unsigned long	end;
	int				ret;

	print_list(begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	ret = list_index_pointer(begin_list, node);
	end = get_time();
	printf("\n%s(%p, %p) == %i in %lu microseconds\n", name, begin_list, node, ret, end - start);
	printf("\n");
	return ;
}

void	test_list_index(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_INDEX\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_index_time(ft_list_index, "\tft_list_index", begin_list, ft_list_at(begin_list, position[i]));
	}
	clear_list(begin_list);
	return ;
}
