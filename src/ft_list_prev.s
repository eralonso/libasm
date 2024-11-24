%include "t_list.mac"
%include "conditionals.mac"

global ft_list_prev

; %macro if_else 5-*
; 	cmp %1, %2
; 	%3 %4
; %endmacro

section .text

ft_list_prev: ; rdi(t_list *begin_list), rsi(t_list *node)

	init_return:
		xor rax, rax ; ret = 0

	null_check:
		if rdi, 0, je, finish_function ; if (begin_list == 0) return ret
		if rsi, 0, je, finish_function ; if (node == 0) return ret

	check_is_first:
		if rdi, rsi, je, finish_function ; if (node == begin_list) return ret

	mov rax, rdi ; ret = begin_list
	loop_start:
		if rax, 0, je, finish_function
		if [rax + t_list.next], rsi, je, finish_function
		iter_list_node rax
		jmp loop_start

finish_function:
	ret ; return ret
