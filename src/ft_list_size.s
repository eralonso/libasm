%include "t_list.mac"

global ft_list_size

ft_list_size: ; rdi(begin_list)
	xor rax, rax ; ret = 0

	loop_start:
		test rdi, rdi ; begin_list == 0
		jz loop_end
		inc rax ; ret++
		mov rdi, [rdi + t_list.next] ; begin_list = begin_list->next
		jmp loop_start
	loop_end:
		ret ; return ret
