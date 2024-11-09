%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

; begin_list = a b c d e f
; node1 = b
; node2 = e
; begin_list = a e c d b f

; needed = prev(b), prev(e)

global ft_list_swap

extern ft_list_index
extern ft_list_prev

%macro get_node_index 3
	save_param_registers_4
	mov rdi, %1
	mov rsi, %2
	call ft_list_index ; ft_list_index(begin_list, nodeN)
	recover_param_registers_4
	if rax, 0, jl, .finish_function
	mov %3, rax
%endmacro

%macro non_equal_values_swap 2
	xor %1, %2
	xor %2, %1
	xor %1, %2
%endmacro

%macro swap_deref 4
	push %4
	mov %3, %1
	push %4
	mov %3, %2
	mov %1, %3
	pop %4
	mov %2, %3
	pop %4
%endmacro

%macro get_node_prev 2
	save_param_registers_4
	mov rdi, %1
	mov rsi, %2
	call ft_list_prev ; ft_list_prev(*begin_list, node2)
	recover_param_registers_4
	push rax
%endmacro

section .text

ft_list_swap: ; rdi(t_list **begin_list), rsi(t_list *node1), rdx(t_list *node2)

	.same_node_check:
		if rsi, rdx, je, .finish_function ; node1 == node2

 	.get_nodes_index:
		get_node_index [rdi], rsi, [first_index wrt ..gotpc] ; first_index = get_node_index(*begin_list, node1)
		get_node_index [rdi], rdx, [second_index wrt ..gotpc] ; first_index = get_node_index(*begin_list, node2)

	.sort_index:
		if_deref [first_index wrt ..gotpc], [second_index wrt ..gotpc], jl, .sorted_index, ecx, rcx ; first_index < second_index
	.swap_index:
		swap_deref [first_index wrt ..gotpc], [second_index wrt ..gotpc], ecx, rcx ; first_index <-> second_index
		non_equal_values_swap rsi, rdx ; node1 <-> node2
	.sorted_index:

	.get_first_node_prev:
		if dword [first_index wrt ..gotpc], 0, je, .is_start
	.is_not_start:
		get_node_prev [rdi], rsi
		jmp .get_first_node_prev_end
	.is_start:
		push rdi
	.get_first_node_prev_end:

	.get_second_node_prev:
		get_node_prev [rdi], rdx


	.get_first_node_next:
		push qword [rsi + t_list.next]

	.get_second_node_next:
		push qword [rdx + t_list.next]


	.set_new_first_node_next:
		pop rcx
		mov [rsi + t_list.next], rcx

	.set_new_second_node_next:
		pop rcx
		if rcx, rdx, jne, .second_is_continuous_end
		.is_continuous:
			mov rcx, rsi
		.second_is_continuous_end:

		mov [rdx + t_list.next], rcx

	.set_new_first_node_prev:
		pop rcx
		if rcx, rsi, je, .first_is_continuous_end
		.first_is_not_continuous:
			mov [rcx + t_list.next], rsi
		.first_is_continuous_end:

	.set_new_second_node_prev:
		pop rcx
		if rcx, rdi, jne, .is_not_begin_list
		.is_begin_list:
			mov [rdi], rdx
			jmp .is_begin_list_end
		.is_not_begin_list:
			mov [rcx + t_list.next], rdx
		.is_begin_list_end:

	.finish_function:
		ret

section .data write
	first_index dd 1
	second_index dd 1
