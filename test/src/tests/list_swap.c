#include "tests/list_swap.h"

void	__test_list_swap_time(
		void (*list_swap_pointer)(t_list **, t_list *, t_list *),
		char *name, t_list **begin_list, t_list *node1, t_list *node2)
{
	unsigned long	start;
	unsigned long	end;

	//if (node1)
	//	printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	//if (node2)
	//	printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	print_list_strings(*begin_list);
	start = get_time();
	list_swap_pointer(begin_list, node1, node2);
	end = get_time();
	printf("\n%s(%p, %p, %p) in %lu microseconds\n", name, begin_list, node1, node2, end - start);
	print_list_strings(*begin_list);
	printf("\n");
	return ;
}

void	test_list_swap(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[][2] = {{2, 5}, {-1, 2}, {-1, -1}, {0, 0}, {0, 1}, {0, 6}, {0, 1}, {0, 2}, {0, 1}};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SWAP\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_swap_time(ft_list_swap, "\tft_list_swap",
				&begin_list,
				ft_list_at(begin_list, position[i][0]),
				ft_list_at(begin_list, position[i][1]));
	}
	clear_list(begin_list);
	return ;
}
