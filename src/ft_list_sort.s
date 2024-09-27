%include "t_list.mac"

global ft_list_sort

extern ft_list_size, ft_list_swap

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
	mov rax, rdx
	ret ; return ret

quicksort_partition: ; rdi(begin_list), rsi(cmp), rdx(init), rcx(end), r8(pivot_index)
	
	get_init_node:
		mov r9, rdx
		call get_node ; ret = get_node(begin_list, init)
		mov [init_node], rax

	get_end_node:
		mov r9, rcx
		call get_node ; ret = get_node(begin_list, end)
		mov [end_node], rax

	get_pivot_node:
		mov r9, r8
		call get_node ; ret = get_node(begin_list, pivot_index)
		mov [pivot], [rax + t_list.data] ; pivot = ret->data
		
	loop_start:
		cmp rdx, rcx
		jge loop_end

	loop_end:
		

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

finish_function:
	ret ; return

section .bss
	init_node resq 1
	end_node resq 1
	pivot resq 1
