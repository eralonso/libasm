%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

global ft_list_remove_if

default rel

extern ft_list_del

section .text

ft_list_remove_if: ; rdi(t_list **begin_list), rsi(void *data_ref), rdx(int (*cmp)()), rcx(void (*free_fct)(void *))
	
	null_check:
		if rdi, 0, je, finish_function
		if rdx, 0, je, finish_function

	init_iter:
		mov r8, [rdi]

	list_loop_start:

		.null_check:
			if r8, 0, je, list_loop_end

		.data_cmp:
			save_param_registers_6
			mov rdi, [r8 + t_list.data]
			call rdx
			recover_param_registers_6
			if rax, 0, jne, .iter

		.remove_node:
			save_param_registers_6
			mov rsi, r8
			mov rdx, rcx
			call ft_list_del
			recover_param_registers_6

		.iter:
			iter_list_node r8

		jmp list_loop_start

	list_loop_end:
		
finish_function:
	ret 
