section .text
global ft_strlen

ft_strlen:
	mov rax, rdi ; tmp = str
	while_loop:
		cmp byte [rax], 0 ; *tmp == 0
		je finish_function
		inc rax ; tmp++
		jmp while_loop
	finish_function:
		sub rax, rdi ; tmp -= str
		ret ; end
