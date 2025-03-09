#include "utils/list.h"

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
