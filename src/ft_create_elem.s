%include "t_list.mac"

global ft_create_elem

extern malloc

section .text

ft_create_elem: ; rdi(data)
	push rdi
	mov rdi, t_list_size
	call malloc ; ret = malloc(sizeof(t_list))
	pop rdi
	mov [rax + t_list.data], rdi ; ret->data = data
	ret ; return ret
