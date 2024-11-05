global ft_list_swap

%include "t_list.mac"
%include "conditionals.mac"

section .text

ft_list_swap:

	null_check:
		if rdi, 0, je, finish_function
		if rsi, 0, je, finish_function
		if rdx, 0, je, finish_function

finish_function:
	ret
