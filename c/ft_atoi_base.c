/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:10:18 by eralonso          #+#    #+#             */
/*   Updated: 2024/09/04 16:06:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#ifndef BASE_MIN_SIZE
# define BASE_MIN_SIZE 2
#endif

typedef int	(*t_char_cmp)(int);

typedef t_char_cmp	t_char_checker;
typedef int	(*t_str_checker)(const char *);
typedef int	(*t_atoi_base_test)(void);

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

ssize_t	ft_strchr_count(const char *str, const char c)
{
	int		i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	if (!counter)
		return (-1);
	return (counter);
}

char	convert_sign_to_number(const char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

char	convert_sign_str_n_to_number(const char *str, const size_t n)
{
	int		i;
	char	final_sign;
	int		minus_sign_count;

	i = 0;
	final_sign = 1;
	minus_sign_count = 0;
	while (str[i] && i < n && is_sign_symbol(str[i]))
	{
		if (str[i] == '-')
			minus_sign_count++;
		i++;
	}
	if (minus_sign_count & 1)
		final_sign = -1;
	return (final_sign);
}

char	convert_sign_str_to_number(const char *str)
{
	return (convert_sign_str_n_to_number(str, -1));
}

ssize_t	str_find_first_not_of(const char *str, t_char_cmp cmp)
{
	ssize_t	i;

	i = 0;
	while (str[i] && cmp(str[i]))
		i++;
	if (cmp(str[i]))
		return (-1);
	return (i);
}

ssize_t	ft_strchri(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] != (char)c)
		return (-1);
	return (i);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\n' || c == '\f');
}

int	is_sign_symbol(int c)
{
	return (c == '+' || c == '-');
}

int	has_char_duplicated(const char *str)
{
	int		i;
	int		j;
	char	to_check;

	i = 0;
	while (str[i])
	{
		to_check = str[i];
		j = i + 1;
		while (str[j])
		{
			if (str[j] == to_check)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	str_has_min_size(const char *str, const size_t min_size)
{
	return (str && ft_strlen(str) >= min_size)
}

static int	__has_base_min_size(const char *base)
{
	return (str_has_min_size(base, BASE_MIN_SIZE));
}

static int	__has_base_valid_characters(const char *base)
{
	const t_char_checker	checkers[] = {ft_isspace, is_sign_symbol};
	const int				checkers_amount = \
		sizeof(checkers) / sizeof(*checkers);
	int						checker;
	int						i;

	i = 0;
	while (base[i])
	{
		checker = 0;
		while (checker < checkers_amount)
		{
			if (checkers[checker](base[i]))
				return (0);
			checker++;
		}
		i++;
	}
	return (1);
}

static int	__has_base_no_duplicated(const char *str)
{
	return (!has_char_duplicated(str));
}

short	is_valid_base(const char *base)
{
	const t_str_checker	checkers[] = {
		__has_base_min_size,
		__has_base_valid_characters,
		__has_base_no_duplicated};
	const int				checkers_amount = \
		sizeof(checkers) / sizeof(*checkers);
	int						checker;

	checker = 0;
	while (checker < checkers_amount)
	{
		if (!checkers[checker](base))
			return (0);
		checker++;
	}
	return (1);
};

static int	__convert_to_int_from_base(const char *str, const char *base)
{
	int		value;
	int		i;
	int		number;
	size_t	base_len;

	i = 0;
	value = 0;
	number = 0;
	base_len = ft_strlen(base);
	while (str[i] && value >= 0)
	{
		value = ft_strchri(base, str[i]);
		if (value >= 0)
			number = number * base_len + value;
		i++;
	}
	return (number);
}

static int	__ft_atoi_base(const char *str, const char *base)
{
	int		number;
	char	sign;
	int		pos;
	int		last_sign_pos;

	number = 0;
	sign = 1;
	pos = str_find_first_not_of(str, ft_isspace);
	if (pos == -1)
		return (0);
	if (is_sign_symbol(str[pos]))
	{
		last_sign_pos = str_find_first_not_of(str + pos, is_sign_symbol);
		if (last_sign_pos == -1)
			return (0);
		sign = convert_sign_str_n_to_number(str + pos, last_sign_pos);
		pos += last_sign_pos;
	}
	number = __convert_to_int_from_base(str + pos, base);
	return (number * sign);
}

int	ft_atoi_base(char *str, char *base)
{
	if (!is_valid_base(base) || !str)
		return (0);
	return (__ft_atoi_base(str, base));
}

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
		"      +bab", "     -bab", "    +-bab"
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
		-1, 1, 0,
		0, 1, 1,
		-3, 5, -5,
		5, -5, 0
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

int	main(void)
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
			return (1);
		if (test + 1 < tests_amount)
			write(1, "\n", 1);
		test++;
	}
	return (0);
}
