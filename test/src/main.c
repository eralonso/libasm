#include <stdio.h>

#include "tests.h"

int	main(void)
{
	void	(*tests[])(void) = {
		test_strlen, test_strcpy, test_strcmp,
		test_write, test_read, test_strdup,
		test_convert_sign_to_number, test_strnchri,
		test_strchri, test_is_sign_symbol, 
		test_convert_sign_str_n_to_number, test_isspace,
		test_str_n_find_first_not_of, test_str_find_first_not_of,
		test_has_char_duplicated, test_str_has_min_size,
		test_is_valid_base, atoi_base_main, test_create_elem,
		test_list_push_front, test_list_size, test_list_at,
		test_list_swap_data, test_list_prev,
		test_list_swap, test_list_index, test_list_sort,
		test_list_del, test_list_last, test_list_push_back,
		test_list_remove_if, test_exit
	};
	int		tests_size = sizeof(tests) / sizeof(*tests);

	for	(int test = 0; test < tests_size; test++)
	{
		tests[test]();
		if (test < tests_size - 1)
			printf("\n\n");
	}
	return (0);
}
