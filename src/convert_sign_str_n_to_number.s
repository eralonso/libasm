global convert_sign_str_n_to_number

extern is_sign_symbol

section .text

convert_sign_str_n_to_number:
	xor rcx, rcx
	xor rdx, rdx
	while_loop:
		cmp byte [rdi + rcx], 0
		je calc_final_sign
		cmp rcx, rsi
		je calc_final_sign
		push rdi
		mov rdi, [rdi + rcx]
		call is_sign_symbol
		cmp byte rax, 0
		je calc_final_sign
		cmp byte rdi, [minus_sign]
		jne skip_add_minus_sign
		inc rdx
		skip_add_minus_sign:
			popd rdi
			inc rcx
			jmp while_loop
	

	calc_final_sign:

section .rodata
	minus_sign: db '-'
