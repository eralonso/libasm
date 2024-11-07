%include "t_list.mac"
%include "conditionals.mac"

global ft_list_index

section .text

ft_list_index: ; rdi(*begin_list), rsi(t_list *node)

	.null_check:
		if rdi, 0, je, finish_function_error ; begin_list == 0
		if rdi, 0, je, finish_function_error ; *begin_list == 0
		if rsi, 0, je, finish_function_error ; node == 0

	.init_index:
		xor rax, rax ; index = 0

	.loop_start:
		if rdi, 0, je, finish_function_error
		if rdi, rsi, je, finish_function
		iter_list_node rdi
		inc rax
		jmp .loop_start

finish_function_error:
	mov rax, -1
finish_function:
	ret
