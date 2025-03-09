#include "tests/create_elem.h"

void	__test_create_elem_time(
		t_list *(*create_elem_pointer)(void *), char *name, void *data)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*res;

	start = get_time();
	res = create_elem_pointer(data);
	end = get_time();
	printf("%s(%p) == %p && content == %p && next == %p in %lu microseconds\n", name, data, res, res->data, res->next, end - start);
	free(res);
}

void	test_create_elem(void)
{
	void	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: CREATE_ELEM\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_create_elem_time(ft_create_elem, "\tft_create_elem", strs[i]);
	}
}
