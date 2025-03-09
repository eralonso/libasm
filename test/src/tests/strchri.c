#include "tests/strchri.h"

void	__test_strchri_time(ssize_t (*strchri_pointer)(const char *, int), char *name, const char *str, int c)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			pos;

	start = get_time();
	pos = strchri_pointer(str, c);
	end = get_time();
	printf("%s(%s, %c) == %zi in %lu microseconds\n", name, str, c, pos, end - start);
}

void	test_strchri(void)
{
	char	*strs[] = {"", "", "a", "aaaaaaaaaaaaaaba", "aaaaaaaaaaaaaaba"};
	char	chrs[] = {'-', '\0', 'a', 'a', 'b'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRCHRI\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strchri_time(ft_strchri, "\tft_strchri", strs[i], chrs[i]);
	}
}
