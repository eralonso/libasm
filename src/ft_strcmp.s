section .text
global ft_strcmp

ft_strcmp:
	xor rax, rax ; tmp = 0
	while_loop:
		mov al, byte [rdi] ; tmp = *s1
		cmp al, byte [rsi] ; tmp == *s2
		jne finish_function ; !=
		cmp al, 0 ; tmp == 0
		je finish_function; ==
		inc rdi ; s1++
		inc rsi ; s2++
		jmp while_loop
	finish_function:
		xor rcx, rcx
		mov rcx, [rsi]
		sub rcx, rax 
		mov rax, rcx
		; sub rax, [rsi]
		; jc ft_strcmp
		ret ; end
