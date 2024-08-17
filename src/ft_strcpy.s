section .text
global ft_strcpy

ft_strcpy:
	mov rax, rdi
	while_loop:
		cmp byte [rsi], 0 ; *src == 0
		cmove cl, [rsi] ; tmp = *src ; bl -> Subregister of rbx, lower 8 bits
		mov [rdi], cl ; *dst == tmp
		je finish_function
		inc rdi ; dst++
		inc rsi ; src++
		jmp while_loop
	finish_function:
		ret ; end
