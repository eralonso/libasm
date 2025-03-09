#include "tests/exit.h"

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
