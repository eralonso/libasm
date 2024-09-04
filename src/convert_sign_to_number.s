global convert_sign_to_number

section .text

convert_sign_to_number:
	mov al, 1
	cmp dil, [minus_sign]
	jne finish_function
	neg al
	finish_function:
		ret

section .rodata
	minus_sign: db "-"
