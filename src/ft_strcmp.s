global ft_strcmp

section .text

ft_strcmp: ; rdi(s1), rsi(s2)
	xor rax, rax ; ret = 0
	while_loop:
		mov al, byte [rdi] ; ret = *s1
		cmp al, byte [rsi] ; ret == *s2
		jne finish_function
		cmp al, 0 ; ret == 0
		je finish_function
		inc rdi ; s1++
		inc rsi ; s2++
		jmp while_loop
	finish_function:
		sub al, byte [rsi] ; ret -= *s2
		movsx eax, al ; conversion from byte to doble word
		ret ; return ret

