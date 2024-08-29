section .text
global ft_read

extern __errno_location

ft_read:
	mov rax, 0 ; set system call to read
	syscall ; call
	cmp rax, 0
	jge finish_function ; read(fd, buf, len) >= 0
	manage_errno:
		mov rcx, rax ; tmp = error_value
		call __errno_location ; get errno variable address
		neg rcx ; tmp = -tmp ; absolute value
		mov [rax], rcx ; *errno = tmp
		mov rax, -1 ; return_value = -1
	finish_function:
		ret
