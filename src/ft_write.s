section .text
global ft_write

extern __errno_location

ft_write:
	mov rax, 1 ; set system call to write
	syscall ; call
	cmp rax, 0
	jge finish_function ; write(fd, buf, len) >= 0 
	manage_errno:
		mov rcx, rax ; tmp = error_value
		call __errno_location ; get errno variable address
		neg rcx ; tmp = -tmp ; absolute value
		mov [rax], rcx ; *errno = tmp
		mov rax, -1 ; return_value = -1
	finish_function:
		ret
