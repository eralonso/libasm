#include <stdlib.h>

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
