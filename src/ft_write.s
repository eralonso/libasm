global ft_write

extern __errno_location

section .text

ft_write: ; rdi(fd), rsi(buf), rdx(len)
	mov rax, 1 ; set system call to write
	syscall ; ret = write(fd, buf, len)
	cmp rax, 0 ; ret >= 0
	jge finish_function
	manage_errno:
		mov rcx, rax ; tmp = ret
		call __errno_location wrt ..plt ; ret = &errno ; get errno variable address
		neg rcx ; tmp = -tmp ; absolute value
		mov [rax], rcx ; *ret = tmp
		mov rax, -1 ; ret = -1
	finish_function:
		ret ; return ret
