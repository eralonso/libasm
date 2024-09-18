%include "src/t_list.mac"

global ft_create_elem, t_list

extern malloc

section .text

ft_create_elem: ; rdi(data)
	push rdi
	mov rdi, t_list_size
	call malloc ; ret = malloc(sizeof(t_list))
	pop rcx
	mov [rax + t_list.data], rcx ; ret->data = data
	ret ; return ret
