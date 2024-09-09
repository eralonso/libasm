global ft_strchri

extern ft_strnchri

section .text

ft_strchri:
	mov rdx, -1
	call ft_strnchri
	ret
