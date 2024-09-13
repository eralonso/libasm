global is_valid_base

extern str_has_min_size, has_char_duplicated, ft_isspace, is_sign_symbol

%define BASE_MIN_SIZE 2

section .rodata
	is_valid_base_checkers dq __has_base_min_size, __has_base_no_duplicated, __has_base_valid_characters
	is_valid_base_checkers_amount equ ($ - is_valid_base_checkers) / 8

section .text

is_valid_base: ; rdi(base)
	xor rax, rax ; ret = 0
	xor rcx, rcx ; i = 0

	loop_start_1:
		cmp rcx, is_valid_base_checkers_amount ; i == checkers_amount
		je loop_end_1
		push rdi
		push rcx
		call [is_valid_base_checkers + (rcx * 8)] ; ret = checkers[i](str) ; it's needed multiply for 8 because it's the size of array elements (pointers)
		pop rcx
		pop rdi
		cmp rax, 0 ; ret = 0
		je finish_function
		inc rcx ; i++
		jmp loop_start_1
	loop_end_1:
		mov rax, 1 ; ret = 1
		jmp finish_function

__has_base_min_size: ; rdi(str)
	mov rsi, BASE_MIN_SIZE ; size = BASE_MIN_SIZE (2)
	call str_has_min_size ; ret = str_has_min_size(str, size)
	ret ; return ret

__has_base_no_duplicated: ; rdi(str)
	call has_char_duplicated ; ret = has_char_duplicated(str)
	test rax, rax ; ret & ret
	mov rax, 0 ; ret = 0
	sete al ; set 1 in 8 lower bits rax register if ZF (zero flag) is set and 0 otherwise. Because it only affects 8 lower bits it's needed to clear rax before doing this operation 
	ret ; return ret

section .rodata
	__has_base_valid_characters_checkers dq ft_isspace, is_sign_symbol
	__has_base_valid_characters_checkers_amount equ ($ - __has_base_valid_characters_checkers) / 8 

section .text

__has_base_valid_characters: ; rdi(str)
	xor rax, rax ; ret = 0
	xor rcx, rcx ; i = 0

	str_iter_loop_start:
		cmp byte [rdi + rcx], 0 ; str[i] == 0
		je str_iter_loop_end
		xor rdx, rdx ; j = 0
		loop_start_2:
			cmp rdx, __has_base_valid_characters_checkers_amount ; j == checkers_amount
			je loop_end_2
			push rdi ; save str
			push rcx ; save i
			push rdx ; save j
			movzx rdi, byte [rdi + rcx]
			call [__has_base_valid_characters_checkers + (rdx * 8)] ; ret = checkers[j](str[i]) ; it's needed multiply for 8 because it's the size of array elements (pointers)
			pop rdx ; recover j
			pop rcx ; recover i
			pop rdi ; recover str
			cmp rax, 0 ; ret == 0
			mov rax, 0 ; ret = 0
			jnz finish_function
			inc rdx ; j++
			jmp loop_start_2
		loop_end_2:
			inc rcx ; i++
			jmp str_iter_loop_start
	str_iter_loop_end:
		mov rax, 1 ; ret = 1
		jmp finish_function

finish_function:
	ret ; return ret
