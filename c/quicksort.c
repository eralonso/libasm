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

void	int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return ;
}

int	qs__get_optimal_pivot(int *arr, int init, int end)
{
	int	pivot_index;
	int	mid_size;
	int	i;
	int	tmp;

	mid_size = (end - init) / 2;
	i = init;
	pivot_index = init;
	tmp = int_end;
	while (i < mid_size)
	{
		if (arr[i] > arr[pivot_index])
			pivot_index = i;
		i++;
	}
	return (pivot_index);
}

int	qs__set_rigth_place_pivot(int *arr, int init, int end, int pivot_index)
{
	int	i;
	int	j;
	int	pivot;

	i = init;
	j = end;
	pivot = arr[pivot_index];
	while (i < j)
	{
		while (arr[i] <= pivot && i <= end - 1)
			i++;
		while (arr[j] > pivot && j >= init + 1)
			j--;
		if (i >= j)
			break ;
		int_swap(arr + i, arr + j);
		if (i == pivot_index)
			pivot_index = j;
		else if (j == pivot_index)
			pivot_index = i;
	}
	int_swap(arr + pivot_index, arr + j);
	return (j);
}

// 1: 8 3 4 7 2 1 5 9 6 -> low = 0 | high = 8
// pivot: 8
// 8 3 4 7 2 1 5 6 9
// 6 3 4 7 2 1 5 8 9
// pivot index: 7
// 2.1: 6 3 4 7 2 1 5 -> low = 0 | high = 6
// pivot: 6
// 6 3 4 5 2 1 7
// 1 3 4 5 2 6 7
// pivot index: 5
// 2.2: 9 -> low = 8 | high = 8 // Because low isn't lower than high then it's already sort
// 2.1.1: 1 3 4 5 2 -> low = 0 | high = 4
// pivot: 1
// 1 3 4 5 2 // There isn't a lower number than pivot
// pivot index: 0
// 2.1.2: 7 -> low = 6 | high = 6 // Because low isn't lower than high then it's already sort
// 2.1.1.1: Out Of Range -> low = 0 | high = -1 // Because low isn't lower than high then it's not neccessary sort
// 2.1.1.2: 3 4 5 2 -> low = 1 | high = 4
// pivot: 3
// 3 2 5 4
// 2 3 5 4
// pivot index: 2
// 2.1.1.2.1: 2 -> low = 1 | high = 1 // Because low isn't lower than high then it's already sort
// 2.1.1.2.2: 5 4 -> low = 3 | high = 4
// pivot: 5
// 4 5 // This swap is made outside the while loop
// pivot index: 4
// 2.1.1.2.2.1: 4 -> low = 3 | high = 3 // Because low isn't lower than high then it's already sort
// 2.1.1.2.2.2: 6 -> low = 5 | high = 4 // Because low isn't lower than high then it's already sort

void	qs__loop(int *arr, int init, int end)
{
	int	pivot_index;

	if (init < end)
	{
		pivot_index = qs__get_optimal_pivot(arr, init, end);
		// printf("pivot index: %zu\n", pivot_index);
		pivot_index = qs__set_rigth_place_pivot(arr, init, end, pivot_index);
		qs__loop(arr, init, pivot_index - 1);
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
	int		n[5][100] = {
		{9, 1, 8, 2, -4, int_end},
		{0, 1, int_end},
		{-1, -1, int_end},
		{1, 34, 6, 76, 23, -1, -2147483647, 2147483647, 34, 1, 43, int_end},
		{1234, 12345, 12, 123456, 234, 456, -123, 123453, -1234, int_end}
	};
	int		n_arr_amount = sizeof(n) / sizeof(*n);
	short	is_sorted;

	for (int test = 0; test < n_arr_amount; test++)
	{
		printf("BEFORE:\n");
		print_array_numbers(n[test]);
		quicksort(n[test]);
		printf("AFTER:\n");
		print_array_numbers(n[test]);
		is_sorted = int_arr_issorted(n[test]);
		printf("is_sorted: \033[1;9%cm%s\033[0m\n", is_sorted == 1 ? '2' : '1', get_string_bool(is_sorted));
		printf("\n");
	}
	return ;
}

int	main(void)
{
	test_quicksort();
	return (0);
}
