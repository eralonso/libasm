global has_char_duplicated

section .text

has_char_duplicated: ; rdi(str)
    xor rax, rax ; ret = 0
    xor rcx, rcx ; i = 0
    L1:
        cmp byte [rdi + rcx], 0 ; str[i]
        je finish_function
        mov sil, byte [rdi + rcx] ; tmp = str[i]
        mov rdx, rcx ; j = i
		inc rdx ; rdx++
        L2:
            cmp byte [rdi + rdx], 0 ; str[j] == 0
            je L1_iter
            cmp byte [rdi + rdx], sil ; str[j] == tmp
            je set_is_duplicated
            inc rdx ;  j++
            jmp L2
        L1_iter:
            inc rcx ; i++
            jmp L1

    set_is_duplicated:
        mov rax, 1 ; ret = 1
    finish_function:
        ret ; return ret
