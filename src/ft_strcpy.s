global ft_strcpy

section .text

ft_strcpy: ; rdi(dst), rsi(src)
	mov rax, rdi ; ret = dst
	while_loop:
		cmp byte [rsi], 0 ; *src == 0
		mov cl, [rsi] ; tmp = *src ; cl -> Subregister of rcx, lower 8 bits
		mov [rdi], cl ; *dst == tmp
		je finish_function
		inc rdi ; dst++
		inc rsi ; src++
		jmp while_loop
	finish_function:
		ret ; return ret
