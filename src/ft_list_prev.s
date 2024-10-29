global ft_list_prev

%macro if 4
	cmp %1, %2
	%3 %4
%endmacro

section .text

ft_list_prev: ; rdi(t_list *begin_list), rsi(t_list *node)

	null_check:
		if rdi, 0, je, finish_function
		if rsi, 0, je, finish_function

	xor rax, rax

finish_function:
	ret ; return ret
