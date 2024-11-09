global is_sign_symbol

section .text

is_sign_symbol:
	xor rax, rax
	xor rcx, rcx
	while_loop:
		cmp qword [sign_symbols_len wrt ..gotpc], rcx
		je finish_function
		cmp byte [sign_symbols + rcx wrt ..gotpc], dil
		je set_is_sign_symbol
		inc rcx
		jmp while_loop
	set_is_sign_symbol:
		mov rax, 1
	finish_function:
		ret

section .rodata
	sign_symbols: db "+-"
	sign_symbols_len: dq $ - sign_symbols
