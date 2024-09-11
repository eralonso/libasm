global convert_sign_to_number

section .text

convert_sign_to_number: ; rdi(c)
	mov al, 1 ; ret = 1
	cmp dil, [minus_sign] ; c == '-'
	jne finish_function
	neg al ; ret = -ret
	finish_function:
		ret ; return ret

section .rodata
	minus_sign: db '-'
