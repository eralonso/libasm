#include "tests/list_swap_data.h"

void	__test_list_swap_data_time(
		void (*list_swap_data_pointer)(t_list *, t_list *), char *name, t_list *node1, t_list *node2)
{
	unsigned long	start;
	unsigned long	end;

	if (node1)
		printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	if (node2)
		printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	start = get_time();
	list_swap_data_pointer(node1, node2);
	end = get_time();
	printf("\n%s(%p, %p) in %lu microseconds\n", name, node1, node2, end - start);
	if (node1)
		printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	if (node2)
		printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	printf("\n");
	return ;
}

void	test_list_swap_data(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[][2] = {{0, -1}, {-1, 2}, {-1, -1}, {0, 0}, {0, 1}, {0, 6}, {0, 1}, {0, 2}, {0, 1}};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SWAP_DATA\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_swap_data_time(ft_list_swap_data, "\tft_list_swap_data",
				ft_list_at(begin_list, position[i][0]),
				ft_list_at(begin_list, position[i][1]));
	}
	clear_list(begin_list);
	return ;
}
