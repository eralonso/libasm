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
v
%macro get_node_index 3
	save_param_registers_4
	mov rdi, %1
	mov rsi, %2
	call ft_list_index ; ft_list_index(*begin_list, node1)
	recover_param_registers_4
	if rax, 0, jl, finish_function
	mov %3, rax
%endmacro

section .text

ft_list_swap: ; rdi(t_list **begin_list), rsi(t_list *node1), rdx(t_list *node2)

	.same_node_check:
		if rsi, rdx, je, finish_function ; node1 == node2

 	.get_nodes_index:
		get_node_index [rdi], rsi, [first_index]
		get_node_index [rdi], rdx, [second_index]

;	.sort_index:
;		if [first_index], [second_index], jl, .sorted_index
;	.swap_index:
;		xor [first_index], [second_index]
;		xor [second_index], [first_index]
;		xor [first_index], [second_index]
;		xor rdx, rsi
;		xor rsi, rdx
;		xor rdx, rsi
;	.sorted_index:
;
;	.first_is_start:
;		if [first_index], 0, je, .is_start
;	.is_start:
;		mov [begin_list], rdx

finish_function:
	ret

section .data
	first_index dd 1
	second_index dd 1
