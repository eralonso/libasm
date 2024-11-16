global ft_isspace

default rel

extern ft_strnchri

section .text

ft_isspace: ; rdi(c)
	mov rsi, rdi
	lea rdi, [is_space.characters]
	mov rdx, is_space.len
	call ft_strnchri ; ret = ft_strnchri(is_space_characters, c, is_space_characters_len)
	cmp rax, -1 ; ret == -1
	je set_false
	mov rax, 1 ; ret = 1
	jmp finish_function
	set_false:
		mov rax, 0 ; ret = 0
	finish_function:
		ret ; return ret

section .rodata
	is_space: 
		.characters db ` \t\n\r\f\v`
		.len equ $ - is_space
