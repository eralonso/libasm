%include "t_list.mac"

global ft_list_push_front

extern ft_create_elem

section .text

ft_list_push_front: ; rdi(begin_list), rsi(data)
	test rdi, rdi ; begin_list == 0
	jz finish_function

	cmp qword [rdi], 0 ; *begin_list == 0
	jz finish_function

	push rdi
	mov rdi, rsi
	call ft_create_elem ; ret = ft_create_elem(data)
	pop rdi

	test rax, rax ; ret == 0
	jz finish_function

	mov rdx, [rdi] ; tmp = *begin_list
	mov [rdi], rax ; *begin_list = ret
	mov [rax + t_list.next], rdx ; ret->next = tmp

	finish_function:
		ret ; return
