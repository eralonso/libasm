global is_sign_symbol

section .text

is_sign_symbol:
	xor rax, rax
	xor rcx, rcx
	while_loop:
		cmp byte [sign_symbols + rcx], 0
		je finish_function
		cmp byte [sign_symbols + rcx], rdi
		je is_sign_symbol
		inc rcx
		jmp while_loop
	is_sign_symbol:
		mov rax, 1
	finish_function:
		ret

section .rodata
	sign_symbols: db "+-", 0
