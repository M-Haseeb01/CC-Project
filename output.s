	.text
	.file	"output.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	print.str@GOTPCREL(%rip), %rdi
	movl	$42, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	print.str,@object               # @print.str
	.section	.rodata,"a",@progbits
	.globl	print.str
print.str:
	.asciz	"%d\n"
	.size	print.str, 4

	.section	".note.GNU-stack","",@progbits
