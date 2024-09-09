global ft_isspace

extern ft_strnchri

section .text

ft_isspace:
	mov rsi, rdi
	mov rdi, is_space_characters
	mov rdx, [is_space_characters_len]
	call ft_strnchri ; ret = ft_strnchri(is_space_characters, c, is_space_characters_len)
	cmp rax, -1 ; ret == -1
	je set_false
	mov rax, 1
	jmp finish_function
	set_false:
		mov rax, 0
	finish_function:
		ret

section .rodata
	is_space_characters: .ascii " \t\n\r\f\v"
	is_space_characters_len: dq $ - is_space_characters
