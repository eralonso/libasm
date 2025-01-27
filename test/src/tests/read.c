#include "tests/read.h"

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
