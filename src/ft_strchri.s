global ft_strchri

section .text

ft_strchri:
	xor rax, rax
	while_loop:
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
