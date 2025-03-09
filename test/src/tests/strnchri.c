#include "tests/strnchri.h"

void	__test_strnchri_time(ssize_t (*strnchri_pointer)(const char *, int, size_t), 
			char *name, const char *str, int c, size_t n)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			pos;

	start = get_time();
	pos = strnchri_pointer(str, c, n);
	end = get_time();
	printf("%s(%s, %c, %zu) == %zi in %lu microseconds\n", name, str, c, n, pos, end - start);
}

void	test_strnchri(void)
{
	char	*strs[] = {"", "", "a", "baaaaaaaaaaaaaaba", "aaaaaaaaaaaaaaba"};
	char	chrs[] = {'-', '\0', 'a', 'a', 'b'};
	char	n[] = {1, 1, 0, 1, -1};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRNCHRI\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strnchri_time(ft_strnchri, "\tft_strnchri", strs[i], chrs[i], n[i]);
	}
}
