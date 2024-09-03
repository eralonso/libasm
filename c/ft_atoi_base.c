/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:10:18 by eralonso          #+#    #+#             */
/*   Updated: 2024/09/03 17:12:38 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

typedef int	(*t_char_checkers)(int);
typedef int	(*t_string_checkers)(const char *);
typedef int	(*t_atoi_base_test)(void);

ssize_t	ft_strchri(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if ((char)c != '\0')
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

static int	__has_base_minum_size(const char *base)
{
	return (base && base[0] && base[1]); // or return (ft_strlen(base) > 1);
}

static int	__has_base_valid_characters(const char *base)
{
	const t_char_checkers	checkers[] = {ft_isspace, is_sign_symbol};
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
	const t_string_checkers	checkers[] = {
		__has_base_minum_size,
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
}

static int	__ft_atoi_base(const char *str, const char *base)
{
	int	number;

	number = 1;
	(void) str;
	(void) base;
	return (number);
}

int	ft_atoi_base(char *str, char *base)
{
	if (!is_valid_base(base))
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
		"a", "a", "a",
		"a", "a", "a",
		"a", "a", "a",
		"a", "a", "a"
	};
	const char	*bases[] = {
		"ab", "aab", "a",
		"ab+", "ab-", "ab+-",
		"a+b", "-ab", "-+ab",
		"+acdeb", "", "acdefrtgb"
	};
	const int	expected_values[] = {
		1, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 1};
	const int	test_amount = sizeof(strs) / sizeof(*strs);

	return (multiple_test_atoi_base(strs, bases, expected_values, test_amount));
}

int	main(void)
{
	const t_atoi_base_test	tests[] = {test_base};
	const int				tests_amount = \
		sizeof(tests) / sizeof(*tests);
	int						test;

	test = 0;
	while (test < tests_amount)
	{
		printf("\033[1;98mTest %i:\n\033[0m", test + 1);
		if (!tests[test]())
			return (1);
		test++;
	}
	//test_atoi_base("a", "ab", 1);
	//test_atoi_base("a", "aab", 0);
	//test_atoi_base("a", "a", 0);
	//test_atoi_base("a", "ab+", 0);
	//test_atoi_base("a", "ab-", 0);
	//test_atoi_base("a", "ab+-", 0);
	//test_atoi_base("a", "a+b", 0);
	//test_atoi_base("a", "-ab", 0);
	//test_atoi_base("a", "-+ab", 0);
	//test_atoi_base("a", "+acdeb", 0);
	//test_atoi_base("a", "acdefrtgb", 1);
	return (0);
}
