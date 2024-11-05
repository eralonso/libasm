%include "t_list.mac"

global ft_list_swap_data

section .text

ft_list_swap_data: ; rdi(node1), rsi(node2)
	
	null_check:
		test rdi, rdi ; node1 == 0
		jz finsih_function
		test rsi, rsi ; node2 == 0
		jz finsih_function
	
	swap_data:
		mov rcx, qword [rdi + t_list.data] ; tmp = node1->data
		mov r8, qword [rsi + t_list.data] ; tmp2 = node2->data
		mov [rdi + t_list.data], r8 ; node1->data = tmp2
		mov [rsi + t_list.data], rcx ; node2->data = tmp

finsih_function:
	ret ; return
