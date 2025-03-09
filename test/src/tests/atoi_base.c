#include "tests/atoi_base.h"

void	__test_atoi_base_time(
		int (*atoi_base_pointer)(const char *, const char *),
		char *name, char *str, char *base)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = atoi_base_pointer(str, base);
	end = get_time();
	printf("%s(%s, %s) == %i in %lu microseconds\n", name, str, base, res, end - start);
}

//void	test_atoi_base(void)
//{
//	char	*strs[] = {"-ab", "", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "     --abc", "01234657"};
//	char	*bases[] = {"ba", "01", "01", "ho", "holamund", "01", "123", "1234", "ba", "01234657"};
//	int		strs_len = sizeof(strs) / sizeof(*strs);
//
//	printf("TEST: ATOI_BASE\n");
//	for (int i = 0; i < strs_len; i++)
//	{
//		printf("TEST %i:\n", i + 1);
//		__test_atoi_base_time(ft_atoi_base, "\tft_atoi_base", strs[i], bases[i]);
//	}
//}

int	test_atoi_base(char *str, char *base, int expected)
{
	int	res;
	int	success;

	res = ft_atoi_base(str, base);
	success = res == expected;
	printf("\033[1;9%cmft_atoi_base(\"%s\", \"%s\") == %i "
		"and expected = %i\n\033[0m",
		success ? '2' : '1', str, base, res, expected);
	return (success);
}

int	multiple_test_atoi_base(const char *strs[], const char *bases[],
		const int expected_values[], const int test_amount)
{
	int			test;

	test = 0;
	while (test < test_amount)
	{
		if (!test_atoi_base((char *)strs[test],
				(char *)bases[test], expected_values[test]))
			return (0);
		test++;
	}
	return (1);
}

int	test_base(void)
{
	const char	*strs[] = {
		"b", "a", "b",
		"b", "b", "b",
		"b", "b", "b",
		"\t", "b", "b"
	};
	const char	*bases[] = {
		"aab", "a", "ab+",
		"ab-", "ab+-", "a+b",
		"-ab", "-+ab", "+acdeb",
		" \t", "\t ab", " +ab"
	};
	const int	expected_values[] = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};
	const int	test_amount = sizeof(strs) / sizeof(*strs);

	return (multiple_test_atoi_base(strs, bases, expected_values, test_amount));
}

int	test_conversion(void)
{
	const char	*strs[] = {
		"a", "b", "ab",
		"ba", "baa", "aaaaaaaaba",
		"bb", "aaabbb", "aaaaaaaaaaaabbbbba",
		"         ba", "b   ab", "   b b a bb",
		"-b", "+b", "-+b",
		"+-ab", "b-", "b-a",
		"-abb+b", " +bab", " -bab",
		"      +bab", "     -bab", "   --+-+-bab"
	};
	const char	*base = "ab";
	//const char	*bases[] = {
	//	"ab", "ab", "ab",
	//	"ab", "ab", "ab",
	//	"ab", "ab", "ab"
	//};
	const int	expected_values[] = {
		0, 1, 1,
		2, 4, 2,
		3, 7, 62,
		2, 1, 1,
		-1, 1, -1,
		-1, 1, 1,
		-3, 5, -5,
		5, -5, 5
	};
	const int	test_amount = sizeof(strs) / sizeof(*strs);
	int			test;

	test = 0;
	while (test < test_amount)
	{
		if (!test_atoi_base((char *)strs[test], (char *)base,
				expected_values[test]))
			return (0);
		test++;
	}
	return (1);
	//return (multiple_test_atoi_base(strs, bases, expected_values, test_amount));
}

void	atoi_base_main(void)
{
	const t_atoi_base_test	tests[] = {test_base, test_conversion};
	const int				tests_amount = \
		sizeof(tests) / sizeof(*tests);
	int						test;

	test = 0;
	while (test < tests_amount)
	{
		printf("\033[1;98mTest %i:\n\033[0m", test + 1);
		if (!tests[test]())
			return ;
		if (test + 1 < tests_amount)
			write(1, "\n", 1);
		test++;
	}
	return ;
}
