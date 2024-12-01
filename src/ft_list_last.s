%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

global ft_list_last

section .text

ft_list_last: ; rdi(t_list *begin_list) -> rax(t_list *last)

	mov rax, rdi

	null_check:
		if rdi, 0, je, finish_function

	loop_start:
		
		.null_check:
			if qword [rax + t_list.next], 0, je, loop_end

		.node_iter:
			iter_list_node rax
		
		jmp loop_start

	loop_end:

finish_function:
	ret
