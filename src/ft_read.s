global ft_read

extern __errno_location

section .text

ft_read: ; rdi(fd), rsi(buf), rdx(len)
	mov rax, 0 ; set system call to read
	syscall ; ret = read(fd, buf, len)
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
