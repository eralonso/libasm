%include "t_list.mac"

global ft_list_sort

extern ft_list_size
extern ft_list_swap

section .text

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
		mv rcx, rax ; end = ret
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
			push rdi
			push rsi
			push rdx
			push rcx
			mov r8, rax
			call quicksort_partition ; ret = quicksort_partition(begin_list, cmp, init, end, pivot_index)
			pop rcx
			pop rdx
			pop rsi
			pop rdi

		sort_first_partition:
			push rdi
			push rsi
			push rdx
			push rcx
			push rax
			mov rcx, rax
			dec rcx
			call quicksort_loop ; quicksort_loop(begin_list, cmp, init, pivot_index - 1)
			pop rax
			pop rcx
			pop rdx
			pop rsi
			pop rdi

		sort_second_partition:
			push rdi
			push rsi
			push rdx
			push rcx
			push rax
			mov rdx, rax
			inc rdx
			call quicksort_loop ; quicksort_loop(begin_list, cmp, pivot_index + 1, end)
			pop rax
			pop rcx
			pop rdx
			pop rsi
			pop rdi

get_optimal_pivot: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end)
	mov rax, rdx ; ret = init
	ret ; return ret

quicksort_partition: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end), r8(pivot_index)
	
	get_init_node:
		mov r9, rdx
		call get_node ; ret = get_node(begin_list, init)
		mov [init_node], rax ; init_node = ret

	get_end_node:
		mov r9, rcx
		call get_node ; ret = get_node(begin_list, end)
		mov [end_node], rax ; end_node = ret

	get_pivot_node:
		mov r9, r8
		call get_node ; ret = get_node(begin_list, pivot_index)
		mov [pivot], [rax + t_list.data] ; pivot = ret->data

	mov [cmp_function], rsi ; cmp_function = cmp
	mov [init_iter], rdx ; init_iter = init
	mov [end_iter], rcx ; end_iter = end
		
	loop_start:
		cmp [init_iter], [end_iter] ; init >= end
		jge loop_end

		loop_1_start:
			push rdi
			push rsi
			mov rdi, [[init_node] + t_list.data]
			mov rsi, [pivot]
			call cmp_function ; ret = cmp_function(init_node->data, pivot)
			pop rsi
			pop rdi
			cmp rax, 0
			jg loop_1_end
			cmp [init_iter], rcx ; init_iter >= end
			jg loop_1_end
			inc byte [init_iter] ; init_iter++		
			mov [init_node], [[init_node] + t_list.next] ; init_node = init_node->next		
			jmp loop_1_start

		loop_1_end:

		loop_2_start:
			push rdi
			push rsi
			mov rdi, [[end_node] + t_list.data]
			mov rsi, [pivot]
			call cmp_function ; ret = cmp_function(end_node->data, pivot)
			pop rsi
			pop rdi
			cmp rax, 0
			jle loop_2_end
			cmp [end_iter], rcx ; end_iter >= end
			jg loop_2_end
			dec byte [end_iter] ; end_iter--
			get_prev_node:
				mov r9, [end_iter]
				call get_node ; ret = get_node(begin_list, end_iter)
				mov [end_iter], rax
			jmp loop_2_start
			
		loop_2_end:

		cmp [init_iter], [end_iter] ; i >= j
		jge loop_end

		push rdi
		push rsi
		push r8
		call ft_list_swap ; ft_list_swap(init_node, end_node)
		pop r8
		pop rsi
		pop rdi

		pivot_moved_check:

			init_iter_check:
				cmp r8, word [init_iter]
				jne end_iter_check
				movsx r8, word [init_iter]
				jmp pivot_moved_check_end

			end_iter_check:
				cmp r8, word [end_iter]
				jne pivot_moved_check_end
				movsx r8, word [end_iter]

		pivot_moved_check_end:

		jmp loop_start

	loop_end:
		push rdi
		push rsi
		push r8
		call ft_list_swap
		pop r8
		pop rsi
		pop rdi

	ret ; return ret
	
	get_node: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end), r8(pivot_index), r9(nbr)
		push rdi
		push rsi
		push rdx
		push rcx
		push r8
		mov rdi, qword [rdi] ; begin_list = *begin_list
		mov rsi, r9
		call ft_list_at ; ret = ft_list_at(begin_list, nbr)
		pop r8
		pop rcx
		pop rdx
		pop rsi
		pop rdi
		ret ; return ret

finish_function:
	ret ; return ret

section .bss
	init_node		resq 1
	end_node		resq 1
	pivot			resq 1
	cmp_function	resq 1
