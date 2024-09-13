global str_has_min_size

extern ft_strlen

section .text

str_has_min_size: ; rdi(str), rsi(size)
	xor rax, rax ; ret = 0

	check_str_is_null:
		cmp rdi, 0 ; str == 0
		je finish_function

	save_size:
		push rsi

	get_str_len:
		call ft_strlen ; ret = ft_strlen(str)

	recover_size:
		pop rsi

	compare_size_len:
		cmp rax, rsi ; ret < size
		mov rax, 0 ; ret = 0 ; Can't set register to 0 with xor instruction due to xor modify eflags and then it change the result of above cmp
		jb finish_function ; When using unsigned values use jb (jump below) or ja (jump above) instructions instead of jl or jg	
		mov rax, 1 ; ret = 1

	finish_function:
		ret ; return ret
