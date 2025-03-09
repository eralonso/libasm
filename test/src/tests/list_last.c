#include "tests/list_last.h"

void	__test_list_last_time(t_list *(*list_last_pointer)(t_list *),
		char *name, t_list *begin_list)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*res;

	printf("BEFORE\n");
	print_list_strings(begin_list);
	start = get_time();
	res = list_last_pointer(begin_list);
	end = get_time();
	printf("%s(%p) == %p && res->data == %s in %lu microseconds\n", name, begin_list, res, (char *)(res ? res->data : NULL), end - start);
	printf("\n");
	return ;
}

void	test_list_last(void)
{
	void			*strs[] = {"2", "1", "0", "8", "4", "9", "7", "3", "5", "6"};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	//for (int i = 0; i < strs_len; i++)
	//	ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_LAST\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_last_time(ft_list_last, "\tft_list_last", begin_list);
		ft_list_push_front(&begin_list, strs[i]);
		if (i & 1)
			ft_list_del(&begin_list, ft_list_last(begin_list), NULL);
	}
	clear_list(begin_list);
	return ;
}
