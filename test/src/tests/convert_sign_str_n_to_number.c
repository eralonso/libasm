#include "tests/convert_sign_str_n_to_number.h"

void	__test_convert_sign_str_n_to_number_time(
		char (*convert_sign_str_n_to_number_pointer)(const char *, const size_t),
		char *name, const char *str, const size_t n)
{
	unsigned long	start;
	unsigned long	end;
	char			sign;

	start = get_time();
	sign = convert_sign_str_n_to_number_pointer(str, n);
	end = get_time();
	printf("%s(%s, %zu) == %i in %lu microseconds\n", name, str, n, sign, end - start);
}

void	test_convert_sign_str_n_to_number(void)
{
	char	*strs[] = {"+", "-", " ", "\0", "a", " +", " -", " --", "++ -", "---+"};
	size_t	n[] = {-1, 1, 1, -1, -1, 4, 4, 5, -1, -1};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: convert_sign_str_n_to_number\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_convert_sign_str_n_to_number_time(convert_sign_str_n_to_number, "\tconvert_sign_str_n_to_number", strs[i], n[i]);
	}
}
