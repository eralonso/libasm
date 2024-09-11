global str_n_find_first_not_of

section .text

str_n_find_first_not_of: ; rdi(str), rsi(cmp_function), rdx(n)
    xor rcx, rcx ; i = 0
    while_loop:
        cmp rcx, rdx ; i == n
        je set_not_found
        push rdi
        push rsi
        push rdx
        push rcx
        movsx rdi, byte [rdi + rcx] ; c = str[i]
        call rsi ; ret = cmp_function(c)
        pop rcx
        pop rdx
        pop rsi
        pop rdi
        cmp rax, 0 ; ret == 0
        je finish_function
        cmp byte [rdi + rcx], 0 ; str[i] == 0
        je set_not_found
        inc rcx ; i++
        jmp while_loop
        
    set_not_found:
        mov rcx, -1 ; i = -1
    finish_function:
        mov rax, rcx ; ret = -1
        ret ; return ret
