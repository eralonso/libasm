global ft_strdup

extern malloc, ft_strlen, ft_strcpy

; malloc uses rcx register for some stuff

section .text

ft_strdup: ; rdi(s)
	call ft_strlen ; ret = ft_strlen(s)
	push rdi ; tmp = s
	mov rdi, rax ; size = ret
	inc rdi ; size++
	call malloc ; ret = malloc(size)
	mov rdi, rax ; dst = ret
	pop rsi ; src = tmp
	call ft_strcpy ; ret = ft_strcpy(dst, src)
	ret ; return ret
