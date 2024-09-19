global str_find_first_not_of

extern ft_strlen
extern str_n_find_first_not_of

section .text

str_find_first_not_of: ; rdi(str), rsi(cmp_function)
	push rsi
	call ft_strlen ; ret = ft_strlen(str)
	pop rsi
    mov rdx, rax ; n = ret
    call str_n_find_first_not_of ; ret = str_n_find_first_not_of(str, cmp_function, n)
    ret ; return ret
