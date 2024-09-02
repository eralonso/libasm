#include <unistd.h>
#include <stdio.h>

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t');
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
		while (str[j] && str[j] == to_check)
			j++;
		i++;
	}
	return (0);
}

static int	__has_base_minum_size(const char *base)
{
	return (base && base[0] && base[1]); // or return (ft_strlen(base) > 1);
}

static int	__has_base_invalid_characters(const char *base)
{
	int	(*checkers[])(int) = {ft_isspace, is_sign_symbol};
	int	checkers_amount = sizeof(checkers) / sizeof(*checkers);
	int			checker;
	int			i;

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

short	is_valid_base(const char *base)
{
	int	(*checkers[])(const char *) = {__has_base_minum_size, __has_base_invalid_characters};
	int	checkers_amount = sizeof(checkers) / sizeof(*checkers);
	int			checker;

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

	number = 0;
	(void) str;
	(void) base;
	return (number);
}

int	ft_atoi_base(char *str, char *base)
{
	if (is_valid_base(base))
		return (0);
	return (__ft_atoi_base(str, base));
}

void	test_atoi_base(char *str, char *base, int expected)
{
	printf("return value = %i and expected = %i", ft_atoi_base(str, base), expected);
	return ;
}

int	main(void)
{
	test_atoi_base("a", "ab", 0);
	return (0);
}
