global is_sign_symbol

default rel

section .text

is_sign_symbol:
	xor rax, rax
	xor rcx, rcx
	while_loop:
		mov rdx, sign_symbols.len
		cmp rdx, rcx
		je finish_function
		lea rdx, [sign_symbols.characters]
		add rdx, rcx
		cmp byte [rdx] , dil
		je set_is_sign_symbol
		inc rcx
		jmp while_loop
	set_is_sign_symbol:
		mov rax, 1
	finish_function:
		ret

section .rodata
	sign_symbols:
		.characters db "+-"
		.len equ $ - sign_symbols
