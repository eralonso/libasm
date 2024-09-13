#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>

//TODO: #include "libasm.h"

typedef int (*t_char_cmp)(int);

typedef struct s_entry			t_entry;
typedef struct s_linked_list	t_linked_list;

typedef union	u_entry_function
{
	size_t	(*strlen)(char *str);
} t_entry_function;

struct	s_entry
{
	char				*name;
	t_entry_function	fun;
};

typedef union	u_linked_list_types
{
	t_entry	*entry;
} t_linked_list_types;

struct	s_linked_list
{
	t_linked_list_types	content;
	t_linked_list		*next;
};

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);
char	convert_sign_to_number(const char c);
ssize_t	ft_strnchri(const char *s, int c, size_t n);
ssize_t	ft_strchri(const char *s, int c);
int		is_sign_symbol(int c);
char	convert_sign_str_n_to_number(const char *str, const size_t n);
int		ft_isspace(int c);
ssize_t	str_n_find_first_not_of(const char *str, int (*cmp_function)(int), size_t n);
ssize_t	str_find_first_not_of(const char *str, int (*cmp_function)(int));
int		has_char_duplicated(const char *str);
int		str_has_min_size(const char *str, const size_t min_size);

char	*get_string_bool(int res)
{
	return (res ? "True": "False");
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	__test_strlen_time(size_t (*stringlen)(const char *), char *name, char *str)
{
	unsigned long	start;
	unsigned long	end;
	size_t			len;

	start = get_time();
	len = stringlen(str);
	end = get_time();
	printf("%s(%s) == %zu in %lu microseconds\n", name, "test", len, end - start);
}

void	test_strlen(void)
{
	char	*strs[] = {"", "hola mundo", "sip faaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaunciona"};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRLEN vs FT_STRLEN\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strlen_time(strlen, "\tstrlen", strs[i]);
		__test_strlen_time(ft_strlen, "\tft_strlen", strs[i]);
	}
}

void	__test_strcpy_time(char *(*stringcpy)(char *, const char *), char *name, char *dst, const char *src)
{
	unsigned long	start;
	unsigned long	end;
	char			*returned_dst;

	start = get_time();
	returned_dst = stringcpy(dst, src);
	end = get_time();
	printf("%s(%s, %s): Same dst address == %s, Equal strings == %s, in %lu microseconds\n",
			name, "test", "test2", get_string_bool(returned_dst == dst),
			get_string_bool(!strncmp(returned_dst, src, strlen(src))),
			end - start);
}

void	test_strcpy(void)
{
	char	str1[3];
	char	str2[100];
	char	str3[3000];
	char	*(strs[][2]) = {{str1, ""}, {str2, "hola mundo"}, {str3, "sip faaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaunciona"}};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRCPY vs FT_STRCPY%i\n", strs_len);
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strcpy_time(strcpy, "\tstrcpy", strs[i][0], strs[i][1]);
		//bzero(strs[i], sizeof(*strs[i][0]));
		__test_strcpy_time(ft_strcpy, "\tft_strcpy", strs[i][0], strs[i][1]);
	}
}

void	__test_strcmp_time(int (*stringcmp)(const char *, const char *), char *name, const char *s1, const char *s2)
{
	unsigned long	start;
	unsigned long	end;
	int				diff;

	start = get_time();
	diff = stringcmp(s1, s2);
	end = get_time();
	printf("%s(%s, %s) == %d in %lu microseconds\n", name, "test", "test2", diff, end - start);
}

void	test_strcmp(void)
{
	char	*(strs[][2]) = {{"", ""}, {"hola mundo", "hola mundo"}, {"", "a"}, {"abc", "abd"}, {"abc", "Abcd"}, {"sip faaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionn", "sip faaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaauncionaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaunciona"}};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: STRCMP vs FT_STRCMP\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_strcmp_time(strcmp, "\tstrcmp", strs[i][0], strs[i][1]);
		__test_strcmp_time(ft_strcmp, "\tft_strcmp", strs[i][0], strs[i][1]);
	}
}

void	__test_write_time(ssize_t (*write_pointer)(int, const void *, size_t), char *name, int fd, char *buf, size_t count)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			written;

	start = get_time();
	written = write_pointer(fd, buf, count);
	end = get_time();
	printf("%s(%i, %s, %zu) == %zd && errno == %i, in %lu microseconds\n", name, fd, "test", count, written, errno, end - start);
}

void	test_write(void)
{
	char	*strs[] = {"", "hola mundo", "sip faaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
	int		fd[] = {1, -1};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	int		fd_len = sizeof(fd) / sizeof(*fd);

	printf("TEST: WRITE vs FT_WRITE\n");
	for (int i = 0; i < fd_len; i++)
	{
		for (int j = 0; j < strs_len; j++)
		{
			printf("TEST %i:\n", (i * strs_len) + j + 1);
			__test_write_time(write, "\twrite", fd[i], strs[j], strlen(strs[j]));
			__test_write_time(ft_write, "\tft_write", fd[i], strs[j], strlen(strs[j]));
		}
	}
}

void	__test_read_time(ssize_t (*read_pointer)(int, void *, size_t), char *name, int fd, char *buf, size_t count)
{
	unsigned long	start;
	unsigned long	end;
	ssize_t			written;

	start = get_time();
	written = read_pointer(fd, buf, count);
	end = get_time();
	printf("%s(%i, %s, %zu) == %zd && errno == %i, buf == %s, in %lu microseconds\n", name, fd, "test", count, written, errno, buf, end - start);
}

void	test_read(void)
{
	size_t	strs_size[] = {1, 10, 100};
	char	*strs[] = {calloc(strs_size[0], sizeof(char)), calloc(strs_size[1], sizeof(char)), calloc(strs_size[2], sizeof(char))};
	int		fd[] = {0, -1};
	int		strs_len = sizeof(strs) / sizeof(*strs);
	int		fd_len = sizeof(fd) / sizeof(*fd);

	printf("TEST: READ vs FT_READ\n");
	for (int i = 0; i < fd_len; i++)
	{
		for (int j = 0; j < strs_len; j++)
		{
			printf("TEST %i:\n", (i * strs_len) + j + 1);
			__test_read_time(read, "\tread", fd[i], strs[j], strs_size[j] - 1);
			__test_read_time(ft_read, "\tft_read", fd[i], strs[j], strs_size[j] - 1);
		}
	}
	for (int i = 0; i < strs_len; i++)
		free(strs[i]);
}

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

void	__test_convert_sign_to_number_time(char (*convert_sign_to_number_pointer)(const char ), char *name, const char c)
{
	unsigned long	start;
	unsigned long	end;
	char			sign;

	start = get_time();
	sign = convert_sign_to_number_pointer(c);
	end = get_time();
	printf("%s(%c) == %i in %lu microseconds\n", name, c, sign, end - start);
}

void	test_convert_sign_to_number(void)
{
	char	strs[] = {'-', '+', 'a'};
	int		strs_len = sizeof(strs) / sizeof(*strs);

	printf("TEST: CONVERT_SIGN_TO_NUMBER\n");
	for (int i = 0; i < strs_len; i++)
	{
		printf("TEST %i:\n", i + 1);
		__test_convert_sign_to_number_time(convert_sign_to_number, "\tconvert_sign_to_number", strs[i]);
	}
}

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

#include <limits.h>

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

int	main(void)
{
	void	(*tests[])(void) = {
		test_strlen, test_strcpy, test_strcmp,
		test_write, test_read, test_strdup,
		test_convert_sign_to_number, test_strnchri,
		test_strchri, test_is_sign_symbol, 
		test_convert_sign_str_n_to_number, test_isspace,
		test_str_n_find_first_not_of, test_str_find_first_not_of,
		test_has_char_duplicated, test_str_has_min_size
	};
	
	int		tests_size = sizeof(tests) / sizeof(*tests);

	for	(int test = tests_size - 1; test < tests_size; test++)
	{
		tests[test]();
		if (test < tests_size - 1)
			printf("\n\n");
	}
	return (0);
}
