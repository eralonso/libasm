section .text
global ft_strlen

ft_strlen:
	mov rbx, rdi
	xor rcx, rcx
	while_loop:
		cmp byte [rbx + rcx], 0
		je finish
		inc rcx
		jmp while_loop

finish:
	mov rax, rcx
	ret
