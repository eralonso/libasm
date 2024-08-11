section .text
global ft_strlen

ft_strlen:
	xor rax, rax ; i = 0
	while_loop:
		cmp byte [rdi + rax], 0 ; str[i] == 0
		je finish_function
		inc rax ; i++
		jmp while_loop
	finish_function:
		ret ; end
