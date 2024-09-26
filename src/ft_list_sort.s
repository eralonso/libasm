%include "t_list.mac"

global ft_list_sort

extern ft_list_size

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
	

finish_function:
	ret ; return
