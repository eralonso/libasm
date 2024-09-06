global convert_sign_str_n_to_number

extern is_sign_symbol

section .text

convert_sign_str_n_to_number: ; rdi(str), rsi(n)
	xor rcx, rcx ; i = 0
	xor rdx, rdx ; minus_sign_count = 0
	while_loop:
		cmp byte [rdi + rcx], 0 ; str[i] == 0
		je calc_final_sign
		cmp rcx, rsi ; i >= n
		jge calc_final_sign
		push rdx
		push rcx
		push rdi ; store str in stack
		mov rdi, [rdi + rcx] ; set rdi to character in position str[i]
		call is_sign_symbol ; ret = is_sign_symbol(str[i])
		mov r8, rdi
		pop rdi
		pop rcx
		pop rdx
		cmp al, 0 ; ret == 0
		je calc_final_sign
		cmp byte r8, [minus_sign] ; str[i] != '-'
		jne skip_add_minus_sign
		inc rdx ; minus_sign_count++
		skip_add_minus_sign:
			;pop rdi ; recover str from stack
			inc rcx ; i++
			jmp while_loop
	calc_final_sign:
		mov al, 1 ; ret = 1
		and rdx, 1 ; minus_sign_count & 1; Check if the number of '-' is odd
		cmp rdx, 0 ; minus_sign_count == 0 ; Then is even
		je finish_function
		neg al ; ret = -ret
	finish_function:
		ret

section .rodata
	minus_sign: db '-'
