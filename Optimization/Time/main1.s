	.file	"main.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The sum of the first 1 billion integers is: %lu \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	movl	$0, %eax
.L2:
	addq	$1, %rax
	cmpq	$1000000001, %rax
	jne	.L2
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movabsq	$500000000500000000, %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
