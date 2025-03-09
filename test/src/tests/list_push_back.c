#include "tests/list_push_back.h"

void	__test_list_push_back_time(
		void (*list_push_back_pointer)(t_list **, void *),
		char *name, t_list **begin_list, void *data)
{
	unsigned long	start;
	unsigned long	end;

	printf("BEFORE\n");
	print_list(*begin_list);
	start = get_time();
	list_push_back_pointer(begin_list, data);
	end = get_time();
	printf("%s(%p, %p) in %lu microseconds\n", name, begin_list, data, end - start);
	printf("AFTER\n");
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_push_back(void)
{
	void	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	t_list	*begin_list = NULL;

	printf("TEST: LIST_PUSH_BACK\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_push_back_time(ft_list_push_back, "\tft_list_push_back", &begin_list, strs[i]);
	}
	clear_list(begin_list);
	return ;
}
