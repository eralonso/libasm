#include "tests/str_n_find_first_not_of.h"

void	__test_str_n_find_first_not_of_time(
		ssize_t (*str_n_find_first_not_of_pointer)(const char *, 
		t_char_cmp, size_t), char *name, const char *str,
		t_char_cmp cmp_function, size_t n, char *cmp_function_name)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			pos;

	start = get_time();
	pos = str_n_find_first_not_of_pointer(str, cmp_function, n);
	end = get_time();
	printf("%s(%s, %s, %zu) == %zi in %lu microseconds\n", name, str,
			cmp_function_name, n, pos, end - start);
}

void	test_str_n_find_first_not_of(void)
{
	char		*strs[] = {"a ", " a", "%1a", "abcd1", "1234a", "1111a"};
	t_char_cmp	cmp[] = {isspace, isspace, isalnum, isalpha, isdigit, isalpha};
	char		*cmp_names[] = {"isspace", "isspace", "isalnum", "isalpha", "isdigit", "isalpha"};
	size_t		n[] = {1, 1, 0, 4, 5, -1};
	int			strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STR_N_FIND_FIRST_NOT_OF\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_str_n_find_first_not_of_time(str_n_find_first_not_of, "\tstr_n_find_first_not_of", strs[i], cmp[i], n[i], cmp_names[i]);
	}
}
