#ifndef TESTS_H
# define TESTS_H

#include "./tests/strlen.h"
#include "./tests/strcpy.h"
#include "./tests/strcmp.h"
#include "./tests/write.h"
#include "./tests/read.h"
#include "./tests/strdup.h"
#include "./tests/convert_sign_to_number.h"
#include "./tests/strnchri.h"
#include "./tests/strchri.h"
#include "./tests/is_sign_symbol.h"
#include "./tests/convert_sign_str_n_to_number.h"
#include "./tests/isspace.h"
#include "./tests/str_n_find_first_not_of.h"
#include "./tests/str_find_first_not_of.h"
#include "./tests/has_char_duplicated.h"
#include "./tests/str_has_min_size.h"
#include "./tests/is_valid_base.h"
#include "./tests/atoi_base.h"
#include "./tests/create_elem.h"
#include "./tests/list_push_front.h"
#include "./tests/list_size.h"
#include "./tests/list_at.h"
#include "./tests/list_swap_data.h"
#include "./tests/list_prev.h"
#include "./tests/list_swap.h"
#include "./tests/list_index.h"
#include "./tests/list_sort.h"
#include "./tests/list_del.h"
#include "./tests/list_last.h"
#include "./tests/list_push_back.h"
#include "./tests/list_remove_if.h"
#include "./tests/exit.h"

// ATOI_BASE_MAIN

typedef int	(*t_char_cmp)(int);

typedef t_char_cmp	t_char_checker;
typedef int	(*t_str_checker)(const char *);
typedef int	(*t_atoi_base_test)(void);

//


// TESTING METHOD

typedef struct s_entry			t_entry;
typedef struct s_linked_list	t_linked_list;

typedef union	u_entry_function
{
	size_t	(*strlen)(char *str);
}	t_entry_function;

struct	s_entry
{
	char				*name;
	t_entry_function	fun;
};

typedef union	u_linked_list_types
{
	t_entry	*entry;
}	t_linked_list_types;

struct	s_linked_list
{
	t_linked_list_types	content;
	t_linked_list		*next;
};

//

#endif
