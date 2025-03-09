#include "tests/list_remove_if.h"

void	__test_list_remove_if_time(
		void (*list_remove_if_pointer)(t_list **, void *,
		int (*)(), void (*)(void *)), char *name,
		t_list **begin_list, void *data_ref, int (*cmp)(), void (*del)(void *))
{
	unsigned long	start;
	unsigned long	end;

	print_list(*begin_list);
	printf("data_ref: %s\n", (char *)data_ref);
	start = get_time();
	list_remove_if_pointer(begin_list, data_ref, cmp, del);
	end = get_time();
	printf("\n%s(%p, %p, %p, %p) in %lu microseconds\n", name, begin_list, data_ref, cmp, del, end - start);
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_remove_if(void)
{
	void			*strs[] = {strdup(""), strdup("1"), strdup("aaa"), strdup("holamund"), strdup("holamundo"), strdup("+123"), strdup("1234-"), strdup("01"), "01234657"};
	void			*data_ref[] = {"", "aaa", "01234657", "holamund", "holamundo", "+123", "1234-", "01", "1"};
	void			(*del_function[])(void *) = {free, free, NULL, free, free, free, free, free, free};
	int				(*cmp_function[])(const char*, const char *) = {strcmp, strcmp, strcmp, NULL, strcmp, strcmp, strcmp, strcmp, strcmp};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_back(&begin_list, strs[i]);
	printf("TEST: LIST_REMOVE_IF\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_remove_if_time(ft_list_remove_if, "\tft_list_remove_if",
				&begin_list, data_ref[i], cmp_function[i], del_function[i]);
	}
	print_list(begin_list);
	full_clear_list(begin_list);
	return ;
}
