;
struc t_list
	.next:		resq 1
	.content:	resq 1
endstruc
;

global ft_list_push_front

section .text

ft_list_push_front: ; rdi(begin_list), rsi(data)
	ret ; return ret
