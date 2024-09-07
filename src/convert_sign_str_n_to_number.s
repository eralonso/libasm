global convert_sign_str_n_to_number

extern is_sign_symbol

section .text

convert_sign_str_n_to_number: ; rdi(str), rsi(n)
	xor rcx, rcx ; i = 0
	xor rdx, rdx ; minus_sign_count = 0
	while_loop:
		cmp byte [rdi + rcx], 0 ; str[i] == 0
		je calc_final_sign
		cmp rcx, rsi ; i == n
		je calc_final_sign
		push rdx ; store minus_sign_count in stack
		push rcx ; store i in stack
		push rsi ; store n in stack
		push rdi ; store str in stack
		mov dil, byte [rdi + rcx] ; set dil (lower 8 bits from rdi register) to character in position str[i]
		call is_sign_symbol ; ret = is_sign_symbol(str[i])
		mov r8b, dil ; tmp = str[i]
		pop rdi ; recover str from stack
		pop rsi ; recover n from stack
		pop rcx ; recover i from stack
		pop rdx ; recover minus_sign_count from stack
		cmp al, 0 ; ret == 0
		je calc_final_sign
		cmp r8b, [minus_sign] ; tmp != '-'
		jne skip_add_minus_sign
		inc rdx ; minus_sign_count++
		skip_add_minus_sign:
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
