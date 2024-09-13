global str_has_min_size

extern ft_strlen

section .text

str_has_min_size: ; rdi(str), rsi(size)
	xor rax, rax ; ret = 0
	cmp rdi, 0 ; str == 0
	je finish_function
	push rsi
	call ft_strlen ; ret = ft_strlen(str)
	pop rsi
	; shl rsi, 1
	; shr rsi, 1
	cmp rax, rsi ; ret < size
	mov rax, 0 ; ret = 0 ; Can't set register to 0 with xor instruction due to xor modify eflags and then it change the result of above cmp
	jl finish_function
	mov rax, 1 ; ret = 1
	finish_function:
		ret ; return ret
