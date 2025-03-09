#include "tests/list_del.h"

void	__test_list_del_time(
		void (*list_del_pointer)(t_list **, t_list *, void (*)(void *)), char *name, t_list **begin_list, t_list *node, void (*del)(void *))
{
	unsigned long	start;
	unsigned long	end;

	print_list(*begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	list_del_pointer(begin_list, node, del);
	end = get_time();
	printf("\n%s(%p, %p) in %lu microseconds\n", name, begin_list, node, end - start);
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_del(void)
{
	void			*strs[] = {strdup(""), strdup("1"), strdup("aaa"), strdup("holamund"), strdup("holamundo"), strdup("+123"), strdup("1234-"), strdup("01"), "01234657"};
	void			(*del_function[])(void *) = {NULL, free, free, free, free, free, free, free, free};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_DEL\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_del_time(ft_list_del, "\tft_list_del",
				&begin_list, ft_list_at(begin_list, position[i]), del_function[i]);
	}
	print_list(begin_list);
	full_clear_list(begin_list);
	return ;
}
