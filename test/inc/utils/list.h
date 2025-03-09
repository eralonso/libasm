#ifndef __LIBASM_LIST_H
# define __LIBASM_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "libasm.h"

void	clear_list(t_list *begin);
void	full_clear_list(t_list *begin);
void	print_list(t_list *begin);
void	print_list_strings(t_list *begin);

#endif
