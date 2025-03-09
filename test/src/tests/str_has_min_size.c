#include "tests/str_has_min_size.h"

void	__test_str_has_min_size_time(
		int (*str_has_min_size_pointer)(const char *, size_t), char *name, char *str, size_t size)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = str_has_min_size_pointer(str, size);
	end = get_time();
	printf("%s(%s, %zu) == %i in %lu microseconds\n", name, str, size, res, end - start);
}

void	test_str_has_min_size(void)
{
	char	*strs[] = {"", "hola mund", "hola mundo", "oabcdefghijklmno"};
	size_t	size[] = {0, 10, 10, ULLONG_MAX};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STR_HAS_MIN_SIZE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_str_has_min_size_time(str_has_min_size, "\tstr_has_min_size", strs[i], size[i]);
	}
}
