; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    exit.s                                             :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: eralonso <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/08/02 18:06:52 by eralonso          #+#    #+#              ;
;    Updated: 2024/08/02 18:06:52 by eralonso         ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

section .text

global ft_exit

ft_exit: ; rdi(int n)
	mov rax, 60 ; exit system call number
	syscall
	ret ; return
