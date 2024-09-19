global ft_atoi_base

extern is_valid_base
extern str_find_first_not_of
extern ft_isspace
extern is_sign_symbol
extern convert_sign_str_n_to_number
extern ft_strchri
extern ft_strlen

section .text

ft_atoi_base: ; rdi(str), rsi(base)
    xor rax, rax ; ret = 0

    test rdi, rdi ; str & str
    jz finish_function
    push rax
	push rsi
	push rdi
    mov rdi, rsi
    call is_valid_base ; ret = is_valid_base(base)
    test rax, rax ; ret & ret
    pop rdi
	pop rsi
	pop rax
    jz finish_function
    call __ft_atoi_base ; ret = __ft_atoi_base(str, base)
    ret ; return ret

__ft_atoi_base: ; rdi(str), rsi(base)
	push rsi
	push rdi
    mov rsi, ft_isspace
    call str_find_first_not_of ; ret = str_find_first_not_of(str, ft_isspace)
    cmp rax, 0 ; ret < 0
	pop rdi
	pop rsi
    jl return_zero
	add rdi, rax ; str += ret
    push rsi
    push rdi
	mov rsi, is_sign_symbol
	call str_find_first_not_of ; ret = str_find_first_not_of(str, is_sign_symbol)
    cmp rax, 0 ; ret < 0
    pop rdi
    pop rsi
	jl return_zero
	mov rdx, rax ; last_sign_pos = ret
	push rdx
	push rsi
	push rdi
	mov rsi, rdx
	call convert_sign_str_n_to_number ; ret = convert_sign_str_n_to_number(str, last_sign_pos)
	pop rdi
	pop rsi
	pop rdx
	mov rcx, rax ; sign = ret
    add rdi, rdx ; str += last_sign_pos
	push rcx
    call __convert_to_int_from_base ; ret = __convert_to_int_from_base(str, base)
    pop rcx
	movsx rcx, cl ; extend sign over the entire register ; 0000 1111 -> 1111 1111
    imul rcx ; ret *= sign
    ret ; return ret

__convert_to_int_from_base: ; rdi(str), rsi(base)
	push rsi
	push rdi
	mov rdi, rsi 
	call ft_strlen ; ret = ft_strlen(base)
	pop rdi
	pop rsi

	mov rdx, rax ; base_len = ret
	xor rax, rax ; ret = 0
	xor rcx, rcx ; i = 0

	loop_start:
		cmp byte [rdi], 0 ; *str == 0
		je finish_function
		push rax
		push rdx
		push rsi
		push rdi
		mov r8, rdi
		mov rdi, rsi
		movzx rsi, byte [r8]
		call ft_strchri ; ret = ft_strchri(base, str[i])
		cmp rax, 0 ; ret < 0
		mov rcx, rax ; value = ret
		pop rdi
		pop rsi
		pop rdx
		pop rax
		jl finish_function
		imul rax, rdx ; ret *= base_len
		add rax, rcx ; ret += value
		inc rdi
		jmp loop_start

return_zero:
	mov rax, 0
finish_function:
    ret ; return ret
