	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"The sum of the first 1 billion integers is: %lu \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.section	.text.startup,"ax",@progbits
.LHOTB1:
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	movabsq	$500000000500000000, %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	xorl	%eax, %eax
	popq	%rdx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE1:
	.section	.text.startup
.LHOTE1:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
