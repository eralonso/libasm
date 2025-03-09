#include "tests/str_find_first_not_of.h"

void	__test_str_find_first_not_of_time(
		ssize_t (*str_find_first_not_of_pointer)(const char *, 
		t_char_cmp), char *name, const char *str,
		t_char_cmp cmp_function, char *cmp_function_name)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			pos;

	start = get_time();
	pos = str_find_first_not_of_pointer(str, cmp_function);
	end = get_time();
	printf("%s(%s, %s) == %zi in %lu microseconds\n", name, str,
			cmp_function_name, pos, end - start);
}

void	test_str_find_first_not_of(void)
{
	char		*strs[] = {"a ", " a", "%1a", "abcd1", "1234a", "aaaa"};
	t_char_cmp	cmp[] = {isspace, isspace, isalnum, isalpha, isdigit, isalpha};
	char		*cmp_names[] = {"isspace", "isspace", "isalnum", "isalpha", "isdigit", "isalpha"};
	int			strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STR_FIND_FIRST_NOT_OF\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_str_find_first_not_of_time(str_find_first_not_of, "\tstr_find_first_not_of", strs[i], cmp[i], cmp_names[i]);
	}
}
