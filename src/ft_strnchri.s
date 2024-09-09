global ft_strnchri

section .text

ft_strnchri:
	xor rax, rax
	while_loop:
		cmp rax, rdx
		je set_not_found
		cmp byte [rdi + rax], sil
		je finish_function
		cmp byte [rdi + rax], 0
		je set_not_found
		inc rax
		jmp while_loop
	set_not_found:
		mov rax, -1
	finish_function:
		ret
