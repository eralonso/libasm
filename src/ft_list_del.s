%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

global ft_list_del

default rel


extern free

extern ft_list_prev


section .text

ft_list_del: ; rdi(t_list **begin_list), rsi(t_list *node), rdx(void (*free_fct)(void *))

	null_check:
		if rdi, 0, je, finish_function

	node_is_first:
		if [rdi], rsi, jne, update_list
	
	update_begin_list:
		mov_deref [rdi], [rsi + t_list.next], rcx, rcx
		jmp erase_data
	
	update_list:
		save_param_registers_4
		mov rdi, [rdi]
		call ft_list_prev
		recover_param_registers_4
		if rax, 0, je, finish_function
		mov_deref [rax + t_list.next], [rsi + t_list.next], rcx, rcx

	erase_data:
		save_param_registers_4

		.null_check:
			if rdx, 0, je, erase_node

		mov rdi, [rsi + t_list.data]
		call rdx

	erase_node:
		mov rdi, rsi
		call free wrt ..plt
		recover_param_registers_4

finish_function:
	ret
