#include "tests/has_char_duplicated.h"

void	__test_has_char_duplicated_time(
		int (*has_char_duplicated_pointer)(const char *), char *name, char *str)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = has_char_duplicated_pointer(str);
	end = get_time();
	printf("%s(%s) == %i in %lu microseconds\n", name, str, res, end - start);
}

void	test_has_char_duplicated(void)
{
	char	*strs[] = {"", "hola mund", "hola mundo", "oabcdefghijklmno"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: HAS_CHAR_DUPLICATED\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_has_char_duplicated_time(has_char_duplicated, "\thas_char_duplicated", strs[i]);
	}
}
