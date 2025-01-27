#include "tests/write.h"

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
