#ifndef __LIBASM_ATOI_BASE_H
# define __LIBASM_ATOI_BASE_H

#include <stdio.h>
#include <unistd.h>

#include "utils/time.h"
#include "libasm.h"

//typedef int	(*t_char_cmp)(int);
//
//typedef t_char_cmp	t_char_checker;
//typedef int	(*t_str_checker)(const char *);
typedef int	(*t_atoi_base_test)(void);


//void	test_atoi_base(void);
void	atoi_base_main(void);

#endif
