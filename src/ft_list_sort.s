%include "t_list.mac"
%include "conditionals.mac"
%include "parameters.mac"

global ft_list_sort

extern ft_list_size
extern ft_list_swap
extern ft_list_at
extern exit

section .text

; Registers preserved across function calls: rbx, rsp, rbp, r12-r15

; GENERAL PURPOSE MACROS

%macro	instruction_double_dereference 3-6 ; %1(instruction), %2(first_op), %3(second_op), %4(first_dereferenced_size), %5(second_dereferenced_size), %6(mov_specifier)
	push r10
	mov%6 r10, %5 [%3]
	%1 %4 [%2], r10
	pop r10
%endmacro

%macro	cmp_dereferenced 2-4 ; %1(first), %2(second), %3(first_dereferenced_size), %4(second_dereferenced_size)
	instruction_double_dereference cmp, %1, %2, %3, %4
%endmacro

%macro	mov_dereferenced 2-4 ; %1(first), %2(second), %3(first_dereferenced_size), %4(second_dereferenced_size)
	instruction_double_dereference mov, %1, %2, %3, %4
%endmacro

;

ft_list_sort: ; rdi(begin_list), rsi(cmp)

	null_check:
		test rdi, rdi ; begin_list == 0
		jz finish_function
	
	sort_algorithm:
		call ft_list_quicksort ; ft_list_quicksort(begin_list, cmp)

	ret ; return

ft_list_quicksort: ; rdi(begin_list), rsi(cmp)

	get_list_len:
		push rdi
		push rsi
		mov rdi, qword [rdi] ; begin_list = *begin_list
		call ft_list_size ; ret = ft_list_size(begin_list)
		pop rsi
		pop rdi
	
	perform_quicksort:
		mov rcx, rax ; end = ret
		xor rdx, rdx ; init = 0
		dec rcx ; end--
		call quicksort_loop ; quicksort_loop(begin_list, cmp, init, end)
	
	ret ; return

quicksort_loop: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end)

	sorted_check:
		cmp rdx, rcx ; init >= end
		jge finish_function

	sorting:

		obtain_pivot:
			call get_optimal_pivot ; ret = get_optimal_pivot(begin_list, cmp, init, end)

		make_partition:
			save_param_registers_4
			mov r8, rax
			call quicksort_partition ; ret = quicksort_partition(begin_list, cmp, init, end, pivot_index)
			recover_param_registers_4

		sort_first_partition:
			push rax
			save_param_registers_4
			mov rcx, rax
			dec rcx
			call quicksort_loop ; quicksort_loop(begin_list, cmp, init, pivot_index - 1)
			recover_param_registers_4
			pop rax

		sort_second_partition:
			save_param_registers_4
			mov rdx, rax
			inc rdx
			call quicksort_loop ; quicksort_loop(begin_list, cmp, pivot_index + 1, end)
			recover_param_registers_4

get_optimal_pivot: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end)
	mov rax, rdx ; ret = init
	ret ; return ret

quicksort_partition: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end), r8(pivot_index)
	
	get_init_node:
		mov r9, rdx
		call get_node ; ret = get_node(begin_list, init)
		mov [init_node wrt ..gotpc], rax ; init_node = ret

	get_end_node:
		mov r9, rcx
		call get_node ; ret = get_node(begin_list, end)
		mov [end_node wrt ..gotpc], rax ; end_node = ret

	get_pivot_node:
		mov r9, r8
		call get_node ; ret = get_node(begin_list, pivot_index)
		mov_dereferenced pivot wrt ..gotpc, rax + t_list.data, qword, qword

	init_bss_variables:
		mov [cmp_function wrt ..gotpc], rsi ; cmp_function = cmp
		mov [init_iter wrt ..gotpc], rdx ; init_iter = init
		mov [end_iter wrt ..gotpc], rcx ; end_iter = end
		
	loop_start:

		check_overiter:
			cmp_dereferenced init_iter wrt ..gotpc, end_iter wrt ..gotpc, qword, qword ; init >= end
			jge loop_end

		loop_1_start:

			cmp_init_node_value:
				save_param_registers_6
				mov rdi, [init_node wrt ..gotpc]
				; add rdi, t_list.data
				mov rdi, [rdi + t_list.data]
				; mov rdi, [[init_node] + t_list.data]
				mov rsi, [pivot wrt ..gotpc]
				call [cmp_function wrt ..gotpc] ; ret = cmp_function(init_node->data, pivot)
				recover_param_registers_6
				cmp eax, 0
				jg loop_1_end

			check_init_iter:
				cmp [init_iter wrt ..gotpc], rcx ; init_iter >= end
				jge loop_1_end

			iter_init_iter:
				inc byte [init_iter wrt ..gotpc] ; init_iter++		

			iter_init_node:
				push rdi
				mov rdi, [init_node wrt ..gotpc]
				; add rdi, t_list.next
				mov rdi, [rdi + t_list.next]
				mov [init_node wrt ..gotpc], rdi
				; mov [init_node], [[init_node] + t_list.next] ; init_node = init_node->next		
				pop rdi

			jmp loop_1_start

		loop_1_end:

		loop_2_start:

			cmp_end_node_value:
				save_param_registers_6
				mov rdi, [end_node wrt ..gotpc]
				; add rdi, t_list.data
				mov rdi, [rdi + t_list.data]
				; mov rdi, [[end_node] + t_list.data]
				mov rsi, [pivot wrt ..gotpc]
				call [cmp_function wrt ..gotpc] ; ret = cmp_function(end_node->data, pivot)
				recover_param_registers_6
				cmp eax, 0
				jle loop_2_end

			check_end_iter:
				cmp [end_iter wrt ..gotpc], rdx ; end_iter <= init
				jle loop_2_end

			iter_end_iter:
				dec byte [end_iter wrt ..gotpc] ; end_iter--

			get_prev_node:
				mov r9, [end_iter wrt ..gotpc]
				call get_node ; ret = get_node(begin_list, end_iter)
				mov [end_node wrt ..gotpc], rax

			jmp loop_2_start
			
		loop_2_end:

			check_overiter_2:
				cmp_dereferenced init_iter wrt ..gotpc, end_iter wrt ..gotpc, qword, qword
				jge loop_end

			swap_content:
				save_param_registers_6
				mov rsi, [init_node wrt ..gotpc]
				mov rdx, [end_node wrt ..gotpc]
				call ft_list_swap ; ft_list_swap(begin_list, init_node, end_node)
				recover_param_registers_6

		pivot_moved_check:

			init_iter_check:
				cmp r8, qword [init_iter wrt ..gotpc] ; pivot_index != init_iter
				jne end_iter_check
				mov r8, [end_iter wrt ..gotpc] ; pivot_index = init_iter
				jmp pivot_moved_check_end

			end_iter_check:
				cmp r8, qword [end_iter wrt ..gotpc] ; pivot_index != end_iter
				jne pivot_moved_check_end
				mov r8, [init_iter wrt ..gotpc] ; pivot_index = end_iter

		pivot_moved_check_end:
	
		; mov rdi, 0
		; call exit

		jmp loop_start

	loop_end:

		last_content_swap:
			save_param_registers_6

			get_pivot_index_node:
				mov r9, r8
				call get_node
				mov rsi, rax

			mov rdx, [end_node wrt ..gotpc]
			call ft_list_swap
			recover_param_registers_6
			mov rax, [end_iter wrt ..gotpc]

	ret ; return ret
	
	get_node: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end), r8(pivot_index), r9(nbr)
		save_param_registers_6
		mov rdi, qword [rdi] ; begin_list = *begin_list
		mov rsi, r9
		call ft_list_at ; ret = ft_list_at(begin_list, nbr)
		recover_param_registers_6
		ret ; return ret

finish_function:
	ret ; return ret

section .bss
	init_iter		resq 1
	end_iter		resq 1
	init_node		resq 1
	end_node		resq 1
	pivot			resq 1
	cmp_function	resq 1
