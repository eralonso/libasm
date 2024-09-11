global test_mutable_data

section .data
    test: db `test\n`

section .text
test_mutable_data:
    mov byte [test], 'T'
    mov rax, 1
    mov rdi, 1
    mov rsi, test
    mov rdx, 5
    syscall
    ret
