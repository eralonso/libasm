%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

global ft_list_push_back

extern ft_create_elem
extern ft_list_last

section .text

ft_list_push_back: ; rdi(t_list **begin_list), rsi(void *data)

	null_check:
		if rdi, 0, je, finish_function

	create_elem:
		save_param_registers_2
		mov rdi, rsi
		call ft_create_elem ; ret = ft_create_elem(data)
		recover_param_registers_2

	elem_null_check:
		if rax, 0, je, finish_function

	mov rdx, rax

	get_last_elem:
		save_param_registers_4
		mov rdi, [rdi]
		call ft_list_last
		recover_param_registers_4

	check_empty_list:
		if rax, 0, je, set_first_elem
	push_elem_to_list:
		mov [rax + t_list.next], rdx ; ret->next = new_elem
		jmp finish_function
	set_first_elem:
		mov [rdi], rdx

finish_function:
	ret ; return
