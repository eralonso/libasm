#include "tests/list_sort.h"

void	__test_list_sort_time(
		void (*list_sort_pointer)(t_list **, t_list_data_cmp),
		char *name, t_list **begin_list, t_list_data_cmp cmp)
{
	unsigned long	start;
	unsigned long	end;

	printf("BEFORE\n");
	print_list_strings(*begin_list);
	start = get_time();
	list_sort_pointer(begin_list, cmp);
	end = get_time();
	printf("%s(%p, %s) in %lu microseconds\n", name, begin_list, "strcmp", end - start);
	printf("AFTER\n");
	print_list_strings(*begin_list);
	printf("\n");
	return ;
}

void	test_list_sort(void)
{
	void			*strs[] = {"2", "1", "0", "8", "4", "9", "7", "3", "5", "6"};
	// void			*strs[] = {"8", "7", "6", "5", "4", "3", "2", "0", "1"};
	// void			*strs[] = {"0", "2", "1"};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SORT\n");
	for (int i = 0; i < 1; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_sort_time(ft_list_sort, "\tft_list_sort", &begin_list, atoicmp);
	}
	clear_list(begin_list);
	return ;
}
