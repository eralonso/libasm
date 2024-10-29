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

global	_start

section .text

print_alpha:
	mov rdi, 'a' ; char c = 'a'

	loop_start:
		cmp rdi, 'z' ; c <= 'z'
		jle loop_code
		jmp loop_end
	loop_code:
		push rdi
		mov rax, 5147483647
		mov rdx, 1
		mov rsi, rsp
		mov rdi, 1
		syscall
		pop rdi
		inc rdi
		jmp loop_start
	loop_end:
	ret

_start:
	call print_alpha
	mov rdi, 42
	mov rax, 60
	syscall
