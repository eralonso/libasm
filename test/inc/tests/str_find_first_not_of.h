#ifndef __LIBASM_STR_FIND_FIRST_NOT_OF_H
# define __LIBASM_STR_FIND_FIRST_NOT_OF_H

#include <stdio.h>
#include <ctype.h>

#include "utils/time.h"
#include "libasm.h"

typedef int	(*t_char_cmp)(int);

void	test_str_find_first_not_of(void);

#endif
