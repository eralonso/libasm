%include "t_list.mac"

global ft_list_push_front

section .text

ft_list_push_front: ; rdi(begin_list), rsi(data)
	mov rax, [rdi + t_list.data] ; This is temp, only for check if include directive works
	ret ; return ret
