%include "t_list.mac"

global ft_list_at

ft_list_at: ; rdi(begin_list), rsi(nbr)
	
	init_return_value:
		xor rax, rax ; ret = 0

	null_check:
		test rdi, rdi ; begin_list == 0
		jz finish_function
	
	pre_loop:
		mov rax, rdi ; ret = begin_list
	
	loop_start:
		test rax, rax ; ret == 0
		jz finish_function
		cmp rsi, 0 ; nbr == 0
		je finish_function
		mov rax, [rax + t_list.next] ; ret = ret->next
		dec rsi ; nbr--
		jmp loop_start

finish_function:
	ret ; return ret
