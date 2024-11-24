#include <sys/time.h>
#include <stdlib.h>

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

int	atoicmp(const char *s1, const char *s2)
{
	int	ns1;
	int	ns2;

	ns1 = atoi(s1);
	ns2 = atoi(s2);
	if (ns1 > ns2)
		return (1);
	else if (ns1 < ns2)
		return (-1);
	return (0);
}
