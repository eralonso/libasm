#include <stdio.h>

void	print_array_numbers(int arr[], int amount)
{
	printf("{");
	for (int n = 0; n < amount; n++)
	{
		printf("%i", n[i]);
		if (n + 1 < amount)
			printf(" ");
	}
	printf("}");
}

void	test_quicksort(void)
{
	int	n[][] = {{9, 1, 8, 2, 4}};
	int	n_arr_amount = sizeof(n) / sizeof(*n);

	for (int test = 0; test < test_amount; test++)
	{
		printf("BEFORE:\n");
		print_array_numbers(n[i], sizeof(n[i]) / sizeof(*(n[i])));
		quicksort(n[i]);
		printf("AFTER:\n");
		print_array_numbers(n[i], sizeof(n[i]) / sizeof(*(n[i])));
	}
	return ;
}

int	main(void)
{
	test_quicksort();
	return (0);
}
