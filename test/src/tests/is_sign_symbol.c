#include "tests/is_sign_symbol.h"

void	__test_is_sign_symbol_time(int (*is_sign_symbol_pointer)(int), char *name, int c)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = is_sign_symbol_pointer(c);
	end = get_time();
	printf("%s(%c) == %i in %lu microseconds\n", name, c, res, end - start);
}

void	test_is_sign_symbol(void)
{
	char	strs[] = {'+', ' ', '-', '\0', 'a'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: IS_SIGN_SYMBOL\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_is_sign_symbol_time(is_sign_symbol, "\tis_sign_symbol", strs[i]);
	}
}
