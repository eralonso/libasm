#include <stdio.h>
#include <limits.h>

#ifndef int_end
# define int_end INT_MIN
#endif

void	print_array_numbers(int arr[])
{
	size_t	i;

	i = 0;
	printf("{ ");
	while (arr[i] != int_end)
	{
		if (i > 0)
			printf(", ");
		printf("%i", arr[i]);
		i++;
	}
	printf(" }\n");
}

size_t	int_arrlen(int *arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len] != int_end)
		len++;
	return (len);
}

short	int_arr_issorted(int *arr)
{
	size_t	i;
	int		tmp;

	if (!arr)
		return (0);
	i = 0;
	tmp = arr[0];
	while (arr[i] != int_end)
	{
		if (arr[i] < tmp)
			return (0);
		tmp = arr[i];
		i++;
	}
	return (1);
}

char	*get_string_bool(short expr)
{
	return (expr == 1 ? "true" : "false");
}

void	int_arr_swap(int *arr, size_t i1, size_t i2)
{
	arr[i1] ^= arr[i2];
	arr[i2] ^= arr[i1];
	arr[i1] ^= arr[i2];
	return ;
}

size_t	qs__get_optimal_pivot(int *arr, size_t init, size_t end)
{
	size_t	pivot_index;
	size_t	mid_size;
	size_t	i;

	mid_size = (end - init) / 2;
	i = init;
	pivot_index = init;
	while (i < mid_size)
	{
		if (arr[i] > arr[pivot_index])
			pivot_index++;
		i++;
	}
	return (pivot_index);
}

size_t	qs__set_rigth_place_pivot(int *arr, size_t init, size_t end, size_t pivot_index)
{
	size_t	i;
	size_t	j;

	i = init;
	j = end;
	while (i < j)
	{
		while (arr[i] < arr[pivot_index])
			i++;
		while (j > 0 && arr[j] > arr[pivot_index])
			j--;
		if (arr[i] > arr[j])
		{
			int_arr_swap(arr, i, j);
			if (i == pivot_index)
				pivot_index = j;
			else if (j == pivot_index)
				pivot_index = i;
		}
		else
			break ;
	}
	return (pivot_index);
}

void	qs__loop(int *arr, size_t init, size_t end)
{
	size_t	pivot_index;

	if (init < end)
	{
		pivot_index = qs__get_optimal_pivot(arr, init, end);
		printf("pivot index: %zu\n", pivot_index);
		pivot_index = qs__set_rigth_place_pivot(arr, init, end, pivot_index);
		qs__loop(arr, init, pivot_index);
		qs__loop(arr, pivot_index + 1, end);		
	}
	return ;
}

void	quicksort(int *arr)
{
	size_t	len;

	len = int_arrlen(arr);
	qs__loop(arr, 0, len - 1);
	return ;
}

void	test_quicksort(void)
{
	int	n[3][100] = {{9, 1, 8, 2, -4, int_end}, {0, 1, int_end}, {-1, -1, int_end}};
	int	n_arr_amount = sizeof(n) / sizeof(*n);

	for (int test = 0; test < n_arr_amount; test++)
	{
		printf("BEFORE:\n");
		print_array_numbers(n[test]);
		quicksort(n[test]);
		printf("AFTER:\n");
		print_array_numbers(n[test]);
		printf("is_sorted: %s\n", get_string_bool(int_arr_issorted(n[test])));
		printf("\n");
	}
	return ;
}

int	main(void)
{
	test_quicksort();
	return (0);
}
