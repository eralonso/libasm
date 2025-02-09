#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "libasm.h"
#include "tests.h"
#include "utils.h"

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

void	__test_isspace_time(int (*isspace_pointer)(int), char *name, int c)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = isspace_pointer(c);
	end = get_time();
	printf("%s(%i) == %i in %lu microseconds\n", name, c, res, end - start);
}

void	test_isspace(void)
{
	char	strs[] = {'\0', '\r', ' ', 'f', '\f', '\a', '\b', '\t', 'g', '	', '\v', '\n'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: ft_isspace VS isspace\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_isspace_time(isspace, "\tisspace", strs[i]);
		__test_isspace_time(ft_isspace, "\tft_isspace", strs[i]);
	}
}

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

void	__test_str_has_min_size_time(
		int (*str_has_min_size_pointer)(const char *, size_t), char *name, char *str, size_t size)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = str_has_min_size_pointer(str, size);
	end = get_time();
	printf("%s(%s, %zu) == %i in %lu microseconds\n", name, str, size, res, end - start);
}

void	test_str_has_min_size(void)
{
	char	*strs[] = {"", "hola mund", "hola mundo", "oabcdefghijklmno"};
	size_t	size[] = {0, 10, 10, ULLONG_MAX};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STR_HAS_MIN_SIZE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_str_has_min_size_time(str_has_min_size, "\tstr_has_min_size", strs[i], size[i]);
	}
}

void	__test_is_valid_base_time(
		int (*is_valid_base_pointer)(const char *), char *name, char *str)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	start = get_time();
	res = is_valid_base_pointer(str);
	end = get_time();
	printf("%s(%s) == %i in %lu microseconds\n", name, str, res, end - start);
}

void	test_is_valid_base(void)
{
	char	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: IS_VALID_BASE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_is_valid_base_time(is_valid_base, "\tis_valid_base", strs[i]);
	}
}

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

void	__test_create_elem_time(
		t_list *(*create_elem_pointer)(void *), char *name, void *data)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*res;

	start = get_time();
	res = create_elem_pointer(data);
	end = get_time();
	printf("%s(%p) == %p && content == %p && next == %p in %lu microseconds\n", name, data, res, res->data, res->next, end - start);
	free(res);
}

void	test_create_elem(void)
{
	void	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: CREATE_ELEM\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_create_elem_time(ft_create_elem, "\tft_create_elem", strs[i]);
	}
}

void	clear_list(t_list *begin)
{
	t_list	*tmp;

	while (begin != 0)
	{
		tmp = begin->next;
		free(begin);
		begin = tmp;
	}
	return ;
}

void	full_clear_list(t_list *begin)
{
	t_list	*tmp;

	while (begin != 0)
	{
		tmp = begin->next;
		free(begin->data);
		free(begin);
		begin = tmp;
	}
	return ;
}

void	print_list(t_list *begin)
{
	unsigned int	index;

	printf("list = ");
	index = 0;
	while (begin != 0)
	{
		printf("%u node: %p, node->data: %s", index, begin, (char *)begin->data);
		begin = begin->next;
		if (begin)
			printf(" | ");
		index++;
	}
	printf("\n");
	return ;
}

void	print_list_strings(t_list *begin)
{
	unsigned int	index;

	printf("list = ");
	index = 0;
	while (begin != 0)
	{
		printf("%u node: %p, node->data: %s", index, begin, (char *)begin->data);
		begin = begin->next;
		if (begin)
			printf(" | ");
		index++;
	}
	printf("\n");
	return ;
}

void	__test_list_push_front_time(
		void (*list_push_front_pointer)(t_list **, void *),
		char *name, t_list **begin_list, void *data)
{
	unsigned long	start;
	unsigned long	end;

	printf("BEFORE\n");
	print_list(*begin_list);
	start = get_time();
	list_push_front_pointer(begin_list, data);
	end = get_time();
	printf("%s(%p, %p) in %lu microseconds\n", name, begin_list, data, end - start);
	printf("AFTER\n");
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_push_front(void)
{
	void	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	t_list	*begin_list = NULL;

	printf("TEST: LIST_PUSH_FRONT\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_push_front_time(ft_list_push_front, "\tft_list_push_front", &begin_list, strs[i]);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_size_time(
		int (*list_size_pointer)(t_list *), char *name, t_list *begin_list)
{
	unsigned long	start;
	unsigned long	end;
	int				size;

	start = get_time();
	size = list_size_pointer(begin_list);
	end = get_time();
	printf("%s(%p) == %i in %lu microseconds\n", name, begin_list, size, end - start);
	printf("\n");
	return ;
}

void	test_list_size(void)
{
	void	*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	t_list	*begin_list = NULL;

	printf("TEST: LIST_SIZE\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_size_time(ft_list_size, "\tft_list_size", begin_list);
		ft_list_push_front(&begin_list, strs[i]);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_at_time(
		t_list *(*list_at_pointer)(t_list *, unsigned int), char *name, t_list *begin_list, unsigned int nbr)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*ret;

	print_list(begin_list);
	start = get_time();
	ret = list_at_pointer(begin_list, nbr);
	end = get_time();
	printf("\n%s(%p, %u) == %p  in %lu microseconds\n", name, begin_list, nbr, ret, end - start);
	printf("\n");
	return ;
}

void	test_list_at(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 9};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_AT\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_at_time(ft_list_at, "\tft_list_at", begin_list, position[i]);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_swap_data_time(
		void (*list_swap_data_pointer)(t_list *, t_list *), char *name, t_list *node1, t_list *node2)
{
	unsigned long	start;
	unsigned long	end;

	if (node1)
		printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	if (node2)
		printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	start = get_time();
	list_swap_data_pointer(node1, node2);
	end = get_time();
	printf("\n%s(%p, %p) in %lu microseconds\n", name, node1, node2, end - start);
	if (node1)
		printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	if (node2)
		printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	printf("\n");
	return ;
}

void	test_list_swap_data(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[][2] = {{0, -1}, {-1, 2}, {-1, -1}, {0, 0}, {0, 1}, {0, 6}, {0, 1}, {0, 2}, {0, 1}};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SWAP_DATA\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_swap_data_time(ft_list_swap_data, "\tft_list_swap_data",
				ft_list_at(begin_list, position[i][0]),
				ft_list_at(begin_list, position[i][1]));
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_prev_time(
		t_list *(*list_prev_pointer)(t_list *, t_list *), char *name, t_list *begin_list, t_list *node)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*ret;

	print_list(begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	ret = list_prev_pointer(begin_list, node);
	end = get_time();
	printf("\n%s(%p, %p) == %p && ret->data = %s in %lu microseconds\n",
			name, begin_list, node, ret, ret ? (char *)ret->data : NULL, end - start);
	printf("\n");
	return ;
}

void	test_list_prev(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_PREV\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_prev_time(ft_list_prev, "\tft_list_prev", begin_list, ft_list_at(begin_list, position[i]));
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_swap_time(
		void (*list_swap_pointer)(t_list **, t_list *, t_list *),
		char *name, t_list **begin_list, t_list *node1, t_list *node2)
{
	unsigned long	start;
	unsigned long	end;

	//if (node1)
	//	printf("node1->data: %p (char *) = %s\n", node1->data, (char *)node1->data);
	//if (node2)
	//	printf("node2->data: %p (char *) = %s\n", node2->data, (char *)node2->data);
	print_list_strings(*begin_list);
	start = get_time();
	list_swap_pointer(begin_list, node1, node2);
	end = get_time();
	printf("\n%s(%p, %p, %p) in %lu microseconds\n", name, begin_list, node1, node2, end - start);
	print_list_strings(*begin_list);
	printf("\n");
	return ;
}

void	test_list_swap(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[][2] = {{2, 5}, {-1, 2}, {-1, -1}, {0, 0}, {0, 1}, {0, 6}, {0, 1}, {0, 2}, {0, 1}};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SWAP\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_swap_time(ft_list_swap, "\tft_list_swap",
				&begin_list,
				ft_list_at(begin_list, position[i][0]),
				ft_list_at(begin_list, position[i][1]));
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_index_time(
		int (*list_index_pointer)(t_list *, t_list *), char *name, t_list *begin_list, t_list *node)
{
	unsigned long	start;
	unsigned long	end;
	int				ret;

	print_list(begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	ret = list_index_pointer(begin_list, node);
	end = get_time();
	printf("\n%s(%p, %p) == %i in %lu microseconds\n", name, begin_list, node, ret, end - start);
	printf("\n");
	return ;
}

void	test_list_index(void)
{
	void			*strs[] = {"", "1", NULL, "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_INDEX\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_index_time(ft_list_index, "\tft_list_index", begin_list, ft_list_at(begin_list, position[i]));
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_sort_time(
		void (*list_sort_pointer)(t_list **, t_list_data_cmp),
		char *name, t_list **begin_list, t_list_data_cmp cmp)
{
	unsigned long	start;
	unsigned long	end;

	printf("BEFORE\n");
	print_list_strings(*begin_list);
	start = get_time();
	list_sort_pointer(begin_list, cmp);
	end = get_time();
	printf("%s(%p, %s) in %lu microseconds\n", name, begin_list, "strcmp", end - start);
	printf("AFTER\n");
	print_list_strings(*begin_list);
	printf("\n");
	return ;
}

void	test_list_sort(void)
{
	void			*strs[] = {"2", "1", "0", "8", "4", "9", "7", "3", "5", "6"};
	// void			*strs[] = {"8", "7", "6", "5", "4", "3", "2", "0", "1"};
	// void			*strs[] = {"0", "2", "1"};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_SORT\n");
	for (int i = 0; i < 1; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_sort_time(ft_list_sort, "\tft_list_sort", &begin_list, atoicmp);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_del_time(
		void (*list_del_pointer)(t_list **, t_list *, void (*)(void *)), char *name, t_list **begin_list, t_list *node, void (*del)(void *))
{
	unsigned long	start;
	unsigned long	end;

	print_list(*begin_list);
	printf("node: %p data: %s\n", node, node ? (char *)node->data : NULL);
	start = get_time();
	list_del_pointer(begin_list, node, del);
	end = get_time();
	printf("\n%s(%p, %p) in %lu microseconds\n", name, begin_list, node, end - start);
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_del(void)
{
	void			*strs[] = {strdup(""), strdup("1"), strdup("aaa"), strdup("holamund"), strdup("holamundo"), strdup("+123"), strdup("1234-"), strdup("01"), "01234657"};
	void			(*del_function[])(void *) = {NULL, free, free, free, free, free, free, free, free};
	unsigned int	position[] = {0, -1, 2, 9, 12, 3, 5, 4, 8};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_DEL\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_del_time(ft_list_del, "\tft_list_del",
				&begin_list, ft_list_at(begin_list, position[i]), del_function[i]);
	}
	print_list(begin_list);
	full_clear_list(begin_list);
	return ;
}

void	__test_list_last_time(t_list *(*list_last_pointer)(t_list *),
		char *name, t_list *begin_list)
{
	unsigned long	start;
	unsigned long	end;
	t_list			*res;

	printf("BEFORE\n");
	print_list_strings(begin_list);
	start = get_time();
	res = list_last_pointer(begin_list);
	end = get_time();
	printf("%s(%p) == %p && res->data == %s in %lu microseconds\n", name, begin_list, res, (char *)(res ? res->data : NULL), end - start);
	printf("\n");
	return ;
}

void	test_list_last(void)
{
	void			*strs[] = {"2", "1", "0", "8", "4", "9", "7", "3", "5", "6"};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	//for (int i = 0; i < strs_len; i++)
	//	ft_list_push_front(&begin_list, strs[i]);
	printf("TEST: LIST_LAST\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_last_time(ft_list_last, "\tft_list_last", begin_list);
		ft_list_push_front(&begin_list, strs[i]);
		if (i & 1)
			ft_list_del(&begin_list, ft_list_last(begin_list), NULL);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_push_back_time(
		void (*list_push_back_pointer)(t_list **, void *),
		char *name, t_list **begin_list, void *data)
{
	unsigned long	start;
	unsigned long	end;

	printf("BEFORE\n");
	print_list(*begin_list);
	start = get_time();
	list_push_back_pointer(begin_list, data);
	end = get_time();
	printf("%s(%p, %p) in %lu microseconds\n", name, begin_list, data, end - start);
	printf("AFTER\n");
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_push_back(void)
{
	void	*strs[] = {"", "1", "hola mund", "holamund", "holamundo", "+123", "1234-", "01", "01234657"};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	t_list	*begin_list = NULL;

	printf("TEST: LIST_PUSH_BACK\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_push_back_time(ft_list_push_back, "\tft_list_push_back", &begin_list, strs[i]);
	}
	clear_list(begin_list);
	return ;
}

void	__test_list_remove_if_time(
		void (*list_remove_if_pointer)(t_list **, void *,
		int (*)(), void (*)(void *)), char *name,
		t_list **begin_list, void *data_ref, int (*cmp)(), void (*del)(void *))
{
	unsigned long	start;
	unsigned long	end;

	print_list(*begin_list);
	printf("data_ref: %s\n", (char *)data_ref);
	start = get_time();
	list_remove_if_pointer(begin_list, data_ref, cmp, del);
	end = get_time();
	printf("\n%s(%p, %p, %p, %p) in %lu microseconds\n", name, begin_list, data_ref, cmp, del, end - start);
	print_list(*begin_list);
	printf("\n");
	return ;
}

void	test_list_remove_if(void)
{
	void			*strs[] = {strdup(""), strdup("1"), strdup("aaa"), strdup("holamund"), strdup("holamundo"), strdup("+123"), strdup("1234-"), strdup("01"), "01234657"};
	void			*data_ref[] = {"", "aaa", "01234657", "holamund", "holamundo", "+123", "1234-", "01", "1"};
	void			(*del_function[])(void *) = {free, free, NULL, free, free, free, free, free, free};
	int				(*cmp_function[])(const char*, const char *) = {strcmp, strcmp, strcmp, NULL, strcmp, strcmp, strcmp, strcmp, strcmp};
	int				strs_len = sizeof(strs) / sizeof(*strs);
	t_list			*begin_list = NULL;

	for (int i = 0; i < strs_len; i++)
		ft_list_push_back(&begin_list, strs[i]);
	printf("TEST: LIST_REMOVE_IF\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_list_remove_if_time(ft_list_remove_if, "\tft_list_remove_if",
				&begin_list, data_ref[i], cmp_function[i], del_function[i]);
	}
	print_list(begin_list);
	full_clear_list(begin_list);
	return ;
}

int	get_exit_value(void (*exit_pointer)(int), int value)
{
	int	ret = 37;
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (!pid)
	{
		exit_pointer(value);
		printf("exit fails\n");
		exit(1);
	}
	wait(&status);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	//else if (WIFSIGNALED(status))
	//	ret = WTERMSIG(status);
	return (ret);
}

void	__test_exit_time(void (*exit_pointer)(int), char *name, int value)
{
	unsigned long	start;
	unsigned long	end;
	int				res;

	printf("value: %i\n", value);
	start = get_time();
	res = get_exit_value(exit_pointer, value);
	end = get_time();
	printf("%s(%i) == %i in %lu microseconds\n", name, value, res, end - start);
	printf("\n");
	return ;
}

void	test_exit(void)
{
	int	exit_values[] = {1, 4, 6, 128, -1, 127, 130, 131, 0, 255, 254, 256, 257};
	int tests_len = sizeof(exit_values) / sizeof(*exit_values);

	printf("TEST: EXIT\n");
	for (int i = 0; i < tests_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_exit_time(exit, "\texit", exit_values[i]);
		__test_exit_time(ft_exit, "\tft_exit", exit_values[i]);
	}
	return ;
}

int	main(void)
{
	void	(*tests[])(void) = {
		test_strlen, test_strcpy, test_strcmp,
		test_write, test_read, test_strdup,
		test_convert_sign_to_number, test_strnchri,
		test_strchri, test_is_sign_symbol, 
		test_convert_sign_str_n_to_number, test_isspace,
		test_str_n_find_first_not_of, test_str_find_first_not_of,
		test_has_char_duplicated, test_str_has_min_size,
		test_is_valid_base, atoi_base_main, test_create_elem,
		test_list_push_front, test_list_size, test_list_at,
		test_list_swap_data, test_list_prev,
		test_list_index, test_list_swap, test_list_sort,
		test_list_del, test_list_last, test_list_push_back,
		test_list_remove_if, test_exit
	};
	int		tests_size = sizeof(tests) / sizeof(*tests);

	for	(int test = 0; test < tests_size; test++)
	{
		tests[test]();
		if (test < tests_size - 1)
			printf("\n\n");
	}
	return (0);
}
