global ft_strlen

section .text

ft_strlen:
	mov rax, rdi ; ret = str
	while_loop:
		cmp byte [rax], 0 ; *ret == 0
		je finish_function
		inc rax ; ret++
		jmp while_loop
	finish_function:
		sub rax, rdi ; ret -= str
		ret ; return ret
