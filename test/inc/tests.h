#ifndef TESTS_H
# define TESTS_H

#include "./tests/strlen.h"
#include "./tests/strcpy.h"
#include "./tests/strcmp.h"
#include "./tests/write.h"
#include "./tests/read.h"

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
