#include "tests/list_prev.h"

void	__test_list_prev_time(
		t_list *(*list_prev_pointer)(t_list *, t_list *), char *name, t_list *begin_list, t_list *node)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*ret;

	print_list(begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	ret = list_prev_pointer(begin_list, node);
	end = get_time();
	printf("\n%s(%p, %p) == %p && ret->data = %s in %lu microseconds\n",
			name, begin_list, node, ret, ret ? (char *)ret->data : NULL, end - start);
	printf("\n");
	return ;
}

void	test_list_prev(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_PREV\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_prev_time(ft_list_prev, "\tft_list_prev", begin_list, ft_list_at(begin_list, position[i]));
	}
	clear_list(begin_list);
	return ;
}
