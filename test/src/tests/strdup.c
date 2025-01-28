#include "tests/strdup.h"

void	__test_strdup_time(char *(*strdup_pointer)(const char *), char *name, const char *s)
{
	unsigned long	start;
	unsigned long	end;
	char			*string_duplicated;

	start = get_time();
	string_duplicated = strdup_pointer(s);
	end = get_time();
	printf("%s(%s) == %s && different address == %s && same content == %s && errno == %i, in %lu microseconds\n",
			name, "test", string_duplicated, get_string_bool(string_duplicated != s),
			get_string_bool(!strncmp(string_duplicated, s, strlen(s))),
			errno, end - start);
	free(string_duplicated);
}

void	test_strdup(void)
{
	char	*strs[] = {"patata", "alaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRDUP vs FT_STRDUP\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strdup_time(strdup, "\tstrdup", strs[i]);
		__test_strdup_time(ft_strdup, "\tft_strdup", strs[i]);
	}
}
