#include "tests/is_valid_base.h"

void	__test_is_valid_base_time(
		int (*is_valid_base_pointer)(const char *), char *name, char *str)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = is_valid_base_pointer(str);
	end = get_time();
	printf("%s(%s) == %i in %lu microseconds\n", name, str, res, end - start);
}

void	test_is_valid_base(void)
{
	char	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: IS_VALID_BASE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_is_valid_base_time(is_valid_base, "\tis_valid_base", strs[i]);
	}
}
