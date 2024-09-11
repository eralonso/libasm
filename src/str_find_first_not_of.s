global str_find_first_not_of

extern str_n_find_first_not_of

section .text

str_find_first_not_of: ; rdi(str), rsi(cmp_function)
    mov rdx, -1 ; n = -1
    call str_n_find_first_not_of ; ret = str_n_find_first_not_of(str, cmp_function, n)
    ret ; return ret
