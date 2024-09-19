%include "t_list.mac"

global ft_create_elem

extern malloc

section .text

ft_create_elem: ; rdi(data)
	push rdi
	mov rdi, t_list_size
	call malloc ; ret = malloc(sizeof(t_list))
	pop rdi

	test rax, rax ; rax == 0
	jz finish_function

	mov [rax + t_list.data], rdi ; ret->data = data
	mov qword [rax + t_list.next], 0 ; ret->next = NULL

	finish_function:
		ret ; return ret
