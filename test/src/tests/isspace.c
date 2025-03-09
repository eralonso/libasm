#include "tests/isspace.h"

void	__test_isspace_time(int (*isspace_pointer)(int), char *name, int c)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = isspace_pointer(c);
	end = get_time();
	printf("%s(%i) == %i in %lu microseconds\n", name, c, res, end - start);
}

void	test_isspace(void)
{
	char	strs[] = {'\0', '\r', ' ', 'f', '\f', '\a', '\b', '\t', 'g', '	', '\v', '\n'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: ft_isspace VS isspace\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_isspace_time(isspace, "\tisspace", strs[i]);
		__test_isspace_time(ft_isspace, "\tft_isspace", strs[i]);
	}
}
