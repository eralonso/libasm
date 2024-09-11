global ft_strchri

extern ft_strnchri

section .text

ft_strchri: ; rdi(str), rsi(c)
	mov rdx, -1 ; n = -1
	call ft_strnchri ; ret = ft_strnchri(str, c, n)
	ret ; return ret
