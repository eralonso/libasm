global ft_strnchri

section .text

ft_strnchri: ; rdi(str), rsi(c), rdx(n)
	xor rax, rax ; ret = 0
	while_loop:
		cmp rax, rdx ; ret == n
		je set_not_found
		cmp byte [rdi + rax], sil ; str[ret] == c
		je finish_function
		cmp byte [rdi + rax], 0 ; str[ret] == 0
		je set_not_found
		inc rax ; ret++
		jmp while_loop
	set_not_found:
		mov rax, -1 ; ret = -1
	finish_function:
		ret ; return ret
