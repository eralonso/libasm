; void	print_alpha(void)
; {
; 	char	c;
; 
; 	c = 'a';
; 	while (c <= 'z')
;	{
; 		write(1, &c, 1)
; 		c++;
;	}
; 	return ;
; }

global	print_alpha

section .text

print_alpha:
	movzx rdi, 'a' ; char c = 'a'

	loop_start:
		cmp byte rdi, 'z' ; c <= 'z'
		jle loop_code
		jmp loop_end
		loop_code:
		push rdi
		mov rax, 1
		mov rdi, 1
		pop rsi
		push rsi
		mov rdx, 1
		syscall
		pop rdi
		inc byte rdi
		jmp loop_start
	loop_end:
	ret
