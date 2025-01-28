#include "tests/convert_sign_to_number.h"

void	__test_convert_sign_to_number_time(char (*convert_sign_to_number_pointer)(const char ), char *name, const char c)
{
	unsigned long	start;
	unsigned long	end;
	char			sign;

	start = get_time();
	sign = convert_sign_to_number_pointer(c);
	end = get_time();
	printf("%s(%c) == %i in %lu microseconds\n", name, c, sign, end - start);
}

void	test_convert_sign_to_number(void)
{
	char	strs[] = {'-', '+', 'a'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: CONVERT_SIGN_TO_NUMBER\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_convert_sign_to_number_time(convert_sign_to_number, "\tconvert_sign_to_number", strs[i]);
	}
}
