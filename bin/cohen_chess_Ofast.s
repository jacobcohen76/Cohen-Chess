	.text
	.file	"cohen_chess.cpp"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev,comdat
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev # -- Begin function _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev
	.p2align	4, 0x90
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev,@function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev: # @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev
	.cfi_startproc
# %bb.0:
	movq	%rdi, %rax
	movq	(%rdi), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.LBB0_1
# %bb.2:
	jmp	_ZdlPv                  # TAILCALL
.LBB0_1:
	retq
.Lfunc_end0:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev, .Lfunc_end0-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev
	.cfi_endproc
                                        # -- End function
	.text
	.globl	_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c # -- Begin function _ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c
	.p2align	4, 0x90
	.type	_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c,@function
_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c: # @_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception0
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movl	%r8d, 20(%rsp)          # 4-byte Spill
	movq	%rcx, 120(%rsp)         # 8-byte Spill
	movq	%rdx, %rbp
	movq	%rdi, %r12
	movq	(%rsi), %rsi
	leaq	88(%rsp), %rdi
	movl	$10, %edx
	callq	_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc
	movq	(%rbp), %rsi
.Ltmp0:
	leaq	56(%rsp), %rdi
	movl	$10, %edx
	callq	_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc
.Ltmp1:
# %bb.1:
	leaq	16(%r12), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%rax, (%r12)
	movq	$0, 8(%r12)
	movb	$0, 16(%r12)
	movq	88(%rsp), %rax
	movq	96(%rsp), %rsi
	cmpq	%rsi, %rax
	je	.LBB1_2
# %bb.3:
	subq	%rax, %rsi
	addq	$-32, %rsi
	movq	%rsi, %rdx
	shrq	$5, %rdx
	addq	$1, %rdx
	movl	%edx, %ecx
	andl	$7, %ecx
	cmpq	$224, %rsi
	jae	.LBB1_5
# %bb.4:
	xorl	%ebx, %ebx
.LBB1_23:
	testq	%rcx, %rcx
	je	.LBB1_26
# %bb.24:
	addq	$8, %rax
	negq	%rcx
	.p2align	4, 0x90
.LBB1_25:                               # =>This Inner Loop Header: Depth=1
	movq	(%rax), %rdx
	cmpq	%rdx, %rbx
	cmovbq	%rdx, %rbx
	addq	$32, %rax
	incq	%rcx
	jne	.LBB1_25
.LBB1_26:
	movq	56(%rsp), %rax
	movq	64(%rsp), %rsi
	cmpq	%rsi, %rax
	je	.LBB1_27
.LBB1_28:
	subq	%rax, %rsi
	addq	$-32, %rsi
	movq	%rsi, %rdx
	shrq	$5, %rdx
	addq	$1, %rdx
	movl	%edx, %ecx
	andl	$7, %ecx
	cmpq	$224, %rsi
	jae	.LBB1_30
# %bb.29:
	xorl	%r13d, %r13d
.LBB1_48:
	testq	%rcx, %rcx
	je	.LBB1_51
# %bb.49:
	addq	$8, %rax
	negq	%rcx
	.p2align	4, 0x90
.LBB1_50:                               # =>This Inner Loop Header: Depth=1
	movq	(%rax), %rdx
	cmpq	%rdx, %r13
	cmovbq	%rdx, %r13
	addq	$32, %rax
	incq	%rcx
	jne	.LBB1_50
	jmp	.LBB1_51
.LBB1_2:
	xorl	%ebx, %ebx
	movq	56(%rsp), %rax
	movq	64(%rsp), %rsi
	cmpq	%rsi, %rax
	jne	.LBB1_28
.LBB1_27:
	xorl	%r13d, %r13d
.LBB1_51:
.Ltmp3:
	movsbl	20(%rsp), %ebp          # 1-byte Folded Reload
	leaq	88(%rsp), %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	callq	_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc
.Ltmp4:
# %bb.52:
.Ltmp5:
	leaq	56(%rsp), %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	callq	_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc
.Ltmp6:
# %bb.53:
	movq	%rbx, 128(%rsp)         # 8-byte Spill
	movq	88(%rsp), %rax
	movq	96(%rsp), %rcx
	subq	%rax, %rcx
	sarq	$5, %rcx
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
	movq	%rbp, %rdx
	subq	%rbx, %rdx
	sarq	$5, %rdx
	cmpq	%rcx, %rdx
	cmovaeq	%rcx, %rdx
	testq	%rdx, %rdx
	je	.LBB1_54
# %bb.63:
	movl	$8, %r15d
	xorl	%r14d, %r14d
	jmp	.LBB1_64
	.p2align	4, 0x90
.LBB1_99:                               #   in Loop: Header=BB1_64 Depth=1
	movb	$10, (%rax,%rbp)
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, 1(%rax,%rbp)
	addq	$1, %r14
	movq	88(%rsp), %rax
	movq	96(%rsp), %rcx
	subq	%rax, %rcx
	sarq	$5, %rcx
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
	movq	%rbp, %rdx
	subq	%rbx, %rdx
	sarq	$5, %rdx
	cmpq	%rcx, %rdx
	cmovaeq	%rcx, %rdx
	addq	$32, %r15
	cmpq	%rdx, %r14
	jae	.LBB1_55
.LBB1_64:                               # =>This Inner Loop Header: Depth=1
	cmpq	%r14, %rcx
	jbe	.LBB1_65
# %bb.67:                               #   in Loop: Header=BB1_64 Depth=1
	movq	-8(%rax,%r15), %rcx
	movq	(%rax,%r15), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_69
# %bb.68:                               #   in Loop: Header=BB1_64 Depth=1
	movq	16(%r12), %rax
.LBB1_69:                               #   in Loop: Header=BB1_64 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_70
# %bb.74:                               #   in Loop: Header=BB1_64 Depth=1
.Ltmp9:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp10:
	jmp	.LBB1_75
	.p2align	4, 0x90
.LBB1_70:                               #   in Loop: Header=BB1_64 Depth=1
	testq	%r8, %r8
	je	.LBB1_75
# %bb.71:                               #   in Loop: Header=BB1_64 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_73
# %bb.72:                               #   in Loop: Header=BB1_64 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_75
.LBB1_73:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_75:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	120(%rsp), %rax         # 8-byte Reload
	movq	(%rax), %rcx
	movq	8(%rax), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_77
# %bb.76:                               #   in Loop: Header=BB1_64 Depth=1
	movq	16(%r12), %rax
.LBB1_77:                               #   in Loop: Header=BB1_64 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_78
# %bb.82:                               #   in Loop: Header=BB1_64 Depth=1
.Ltmp11:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp12:
	jmp	.LBB1_83
	.p2align	4, 0x90
.LBB1_78:                               #   in Loop: Header=BB1_64 Depth=1
	testq	%r8, %r8
	je	.LBB1_83
# %bb.79:                               #   in Loop: Header=BB1_64 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_81
# %bb.80:                               #   in Loop: Header=BB1_64 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_83
.LBB1_81:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_83:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	56(%rsp), %rax
	movq	64(%rsp), %rdx
	subq	%rax, %rdx
	sarq	$5, %rdx
	cmpq	%r14, %rdx
	jbe	.LBB1_84
# %bb.86:                               #   in Loop: Header=BB1_64 Depth=1
	movq	-8(%rax,%r15), %rcx
	movq	(%rax,%r15), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_88
# %bb.87:                               #   in Loop: Header=BB1_64 Depth=1
	movq	16(%r12), %rax
.LBB1_88:                               #   in Loop: Header=BB1_64 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_89
# %bb.93:                               #   in Loop: Header=BB1_64 Depth=1
.Ltmp15:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp16:
	jmp	.LBB1_94
	.p2align	4, 0x90
.LBB1_89:                               #   in Loop: Header=BB1_64 Depth=1
	testq	%r8, %r8
	je	.LBB1_94
# %bb.90:                               #   in Loop: Header=BB1_64 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_92
# %bb.91:                               #   in Loop: Header=BB1_64 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_94
.LBB1_92:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_94:                               #   in Loop: Header=BB1_64 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	(%r12), %rax
	movq	8(%r12), %rbp
	leaq	1(%rbp), %rbx
	movl	$15, %ecx
	cmpq	8(%rsp), %rax           # 8-byte Folded Reload
	je	.LBB1_96
# %bb.95:                               #   in Loop: Header=BB1_64 Depth=1
	movq	16(%r12), %rcx
.LBB1_96:                               #   in Loop: Header=BB1_64 Depth=1
	cmpq	%rcx, %rbx
	jbe	.LBB1_99
# %bb.97:                               #   in Loop: Header=BB1_64 Depth=1
.Ltmp17:
	movl	$1, %r8d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp18:
# %bb.98:                               #   in Loop: Header=BB1_64 Depth=1
	movq	(%r12), %rax
	jmp	.LBB1_99
.LBB1_54:
	xorl	%r14d, %r14d
.LBB1_55:
	movzbl	20(%rsp), %edx          # 1-byte Folded Reload
	movl	%edx, 84(%rsp)          # 4-byte Spill
	cmpq	%rcx, %r14
	jae	.LBB1_106
# %bb.56:
	leaq	1(%r13), %rcx
	movq	%rcx, 112(%rsp)         # 8-byte Spill
	movq	%r14, %r15
	shlq	$5, %r15
	orq	$8, %r15
	jmp	.LBB1_57
	.p2align	4, 0x90
.LBB1_148:                              #   in Loop: Header=BB1_57 Depth=1
	movq	(%r12), %rax
.LBB1_149:                              #   in Loop: Header=BB1_57 Depth=1
	addq	$1, %r14
	movb	$10, (%rax,%rbp)
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, 1(%rax,%rbp)
	movq	88(%rsp), %rax
	movq	96(%rsp), %rcx
	subq	%rax, %rcx
	sarq	$5, %rcx
	addq	$32, %r15
	cmpq	%rcx, %r14
	jae	.LBB1_105
.LBB1_57:                               # =>This Inner Loop Header: Depth=1
	movq	-8(%rax,%r15), %rcx
	movq	(%rax,%r15), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_59
# %bb.58:                               #   in Loop: Header=BB1_57 Depth=1
	movq	16(%r12), %rax
.LBB1_59:                               #   in Loop: Header=BB1_57 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_60
# %bb.112:                              #   in Loop: Header=BB1_57 Depth=1
.Ltmp20:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp21:
	jmp	.LBB1_113
	.p2align	4, 0x90
.LBB1_60:                               #   in Loop: Header=BB1_57 Depth=1
	testq	%r8, %r8
	je	.LBB1_113
# %bb.61:                               #   in Loop: Header=BB1_57 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_111
# %bb.62:                               #   in Loop: Header=BB1_57 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_113
.LBB1_111:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_113:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	120(%rsp), %rax         # 8-byte Reload
	movq	(%rax), %rcx
	movq	8(%rax), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_115
# %bb.114:                              #   in Loop: Header=BB1_57 Depth=1
	movq	16(%r12), %rax
.LBB1_115:                              #   in Loop: Header=BB1_57 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_116
# %bb.120:                              #   in Loop: Header=BB1_57 Depth=1
.Ltmp22:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp23:
	jmp	.LBB1_121
	.p2align	4, 0x90
.LBB1_116:                              #   in Loop: Header=BB1_57 Depth=1
	testq	%r8, %r8
	je	.LBB1_121
# %bb.117:                              #   in Loop: Header=BB1_57 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_119
# %bb.118:                              #   in Loop: Header=BB1_57 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_121
.LBB1_119:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_121:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	leaq	40(%rsp), %rax
	movq	%rax, 24(%rsp)
	cmpq	$16, %r13
	jb	.LBB1_131
# %bb.122:                              #   in Loop: Header=BB1_57 Depth=1
	testq	%r13, %r13
	movq	112(%rsp), %rdi         # 8-byte Reload
	js	.LBB1_123
# %bb.125:                              #   in Loop: Header=BB1_57 Depth=1
	testq	%rdi, %rdi
	js	.LBB1_126
# %bb.128:                              #   in Loop: Header=BB1_57 Depth=1
.Ltmp24:
	callq	_Znwm
.Ltmp25:
# %bb.129:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rax, %rbp
	movq	%rax, 24(%rsp)
	movq	%r13, 40(%rsp)
	jmp	.LBB1_130
	.p2align	4, 0x90
.LBB1_131:                              #   in Loop: Header=BB1_57 Depth=1
	leaq	40(%rsp), %rbp
	testq	%r13, %r13
	je	.LBB1_134
# %bb.132:                              #   in Loop: Header=BB1_57 Depth=1
	cmpq	$1, %r13
	jne	.LBB1_130
# %bb.133:                              #   in Loop: Header=BB1_57 Depth=1
	movl	20(%rsp), %eax          # 4-byte Reload
	movb	%al, 40(%rsp)
	leaq	40(%rsp), %rbp
	jmp	.LBB1_134
	.p2align	4, 0x90
.LBB1_130:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rbp, %rdi
	movl	84(%rsp), %esi          # 4-byte Reload
	movq	%r13, %rdx
	callq	memset
.LBB1_134:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%r13, 32(%rsp)
	movb	$0, (%rbp,%r13)
	movq	24(%rsp), %rcx
	movq	32(%rsp), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_136
# %bb.135:                              #   in Loop: Header=BB1_57 Depth=1
	movq	16(%r12), %rax
.LBB1_136:                              #   in Loop: Header=BB1_57 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_137
# %bb.141:                              #   in Loop: Header=BB1_57 Depth=1
.Ltmp27:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp28:
	jmp	.LBB1_142
	.p2align	4, 0x90
.LBB1_137:                              #   in Loop: Header=BB1_57 Depth=1
	testq	%r8, %r8
	je	.LBB1_142
# %bb.138:                              #   in Loop: Header=BB1_57 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_140
# %bb.139:                              #   in Loop: Header=BB1_57 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_142
.LBB1_140:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_142:                              #   in Loop: Header=BB1_57 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	24(%rsp), %rdi
	leaq	40(%rsp), %rax
	cmpq	%rax, %rdi
	je	.LBB1_144
# %bb.143:                              #   in Loop: Header=BB1_57 Depth=1
	callq	_ZdlPv
.LBB1_144:                              #   in Loop: Header=BB1_57 Depth=1
	movq	(%r12), %rax
	movq	8(%r12), %rbp
	leaq	1(%rbp), %rbx
	movl	$15, %ecx
	cmpq	8(%rsp), %rax           # 8-byte Folded Reload
	je	.LBB1_146
# %bb.145:                              #   in Loop: Header=BB1_57 Depth=1
	movq	16(%r12), %rcx
.LBB1_146:                              #   in Loop: Header=BB1_57 Depth=1
	cmpq	%rcx, %rbx
	jbe	.LBB1_149
# %bb.147:                              #   in Loop: Header=BB1_57 Depth=1
.Ltmp30:
	movl	$1, %r8d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp31:
	jmp	.LBB1_148
.LBB1_105:
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
.LBB1_106:
	movq	%rbp, %rax
	subq	%rbx, %rax
	sarq	$5, %rax
	cmpq	%rax, %r14
	movq	128(%rsp), %r15         # 8-byte Reload
	jae	.LBB1_199
# %bb.107:
	leaq	1(%r15), %rax
	movq	%rax, 112(%rsp)         # 8-byte Spill
	movq	%r14, %r13
	shlq	$5, %r13
	orq	$8, %r13
	jmp	.LBB1_108
	.p2align	4, 0x90
.LBB1_197:                              #   in Loop: Header=BB1_108 Depth=1
	movq	(%r12), %rax
.LBB1_198:                              #   in Loop: Header=BB1_108 Depth=1
	addq	$1, %r14
	movb	$10, (%rax,%rbp)
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, 1(%rax,%rbp)
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
	movq	%rbp, %rax
	subq	%rbx, %rax
	sarq	$5, %rax
	addq	$32, %r13
	cmpq	%rax, %r14
	jae	.LBB1_199
.LBB1_108:                              # =>This Inner Loop Header: Depth=1
	leaq	40(%rsp), %rax
	movq	%rax, 24(%rsp)
	cmpq	$16, %r15
	jb	.LBB1_161
# %bb.109:                              #   in Loop: Header=BB1_108 Depth=1
	testq	%r15, %r15
	js	.LBB1_110
# %bb.155:                              #   in Loop: Header=BB1_108 Depth=1
	movq	112(%rsp), %rdi         # 8-byte Reload
	testq	%rdi, %rdi
	js	.LBB1_156
# %bb.158:                              #   in Loop: Header=BB1_108 Depth=1
.Ltmp33:
	callq	_Znwm
.Ltmp34:
# %bb.159:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rax, %rbp
	movq	%rax, 24(%rsp)
	movq	%r15, 40(%rsp)
	jmp	.LBB1_160
	.p2align	4, 0x90
.LBB1_161:                              #   in Loop: Header=BB1_108 Depth=1
	leaq	40(%rsp), %rbp
	testq	%r15, %r15
	je	.LBB1_164
# %bb.162:                              #   in Loop: Header=BB1_108 Depth=1
	cmpq	$1, %r15
	jne	.LBB1_160
# %bb.163:                              #   in Loop: Header=BB1_108 Depth=1
	movl	20(%rsp), %eax          # 4-byte Reload
	movb	%al, 40(%rsp)
	leaq	40(%rsp), %rbp
	jmp	.LBB1_164
	.p2align	4, 0x90
.LBB1_160:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rbp, %rdi
	movl	84(%rsp), %esi          # 4-byte Reload
	movq	%r15, %rdx
	callq	memset
.LBB1_164:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%r15, 32(%rsp)
	movb	$0, (%rbp,%r15)
	movq	24(%rsp), %rcx
	movq	32(%rsp), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_166
# %bb.165:                              #   in Loop: Header=BB1_108 Depth=1
	movq	16(%r12), %rax
.LBB1_166:                              #   in Loop: Header=BB1_108 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_167
# %bb.171:                              #   in Loop: Header=BB1_108 Depth=1
.Ltmp36:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp37:
	jmp	.LBB1_172
	.p2align	4, 0x90
.LBB1_167:                              #   in Loop: Header=BB1_108 Depth=1
	testq	%r8, %r8
	je	.LBB1_172
# %bb.168:                              #   in Loop: Header=BB1_108 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_170
# %bb.169:                              #   in Loop: Header=BB1_108 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_172
.LBB1_170:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_172:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	24(%rsp), %rdi
	leaq	40(%rsp), %rax
	cmpq	%rax, %rdi
	je	.LBB1_174
# %bb.173:                              #   in Loop: Header=BB1_108 Depth=1
	callq	_ZdlPv
.LBB1_174:                              #   in Loop: Header=BB1_108 Depth=1
	movq	120(%rsp), %rax         # 8-byte Reload
	movq	(%rax), %rcx
	movq	8(%rax), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_176
# %bb.175:                              #   in Loop: Header=BB1_108 Depth=1
	movq	16(%r12), %rax
.LBB1_176:                              #   in Loop: Header=BB1_108 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_177
# %bb.181:                              #   in Loop: Header=BB1_108 Depth=1
.Ltmp39:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp40:
	jmp	.LBB1_182
	.p2align	4, 0x90
.LBB1_177:                              #   in Loop: Header=BB1_108 Depth=1
	testq	%r8, %r8
	je	.LBB1_182
# %bb.178:                              #   in Loop: Header=BB1_108 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_180
# %bb.179:                              #   in Loop: Header=BB1_108 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_182
.LBB1_180:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_182:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	56(%rsp), %rax
	movq	64(%rsp), %rdx
	subq	%rax, %rdx
	sarq	$5, %rdx
	cmpq	%r14, %rdx
	jbe	.LBB1_183
# %bb.185:                              #   in Loop: Header=BB1_108 Depth=1
	movq	-8(%rax,%r13), %rcx
	movq	(%rax,%r13), %r8
	movq	(%r12), %rdi
	movq	8(%r12), %rsi
	leaq	(%rsi,%r8), %rbx
	movl	$15, %eax
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_187
# %bb.186:                              #   in Loop: Header=BB1_108 Depth=1
	movq	16(%r12), %rax
.LBB1_187:                              #   in Loop: Header=BB1_108 Depth=1
	cmpq	%rax, %rbx
	jbe	.LBB1_188
# %bb.192:                              #   in Loop: Header=BB1_108 Depth=1
.Ltmp44:
	movq	%r12, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp45:
	jmp	.LBB1_193
	.p2align	4, 0x90
.LBB1_188:                              #   in Loop: Header=BB1_108 Depth=1
	testq	%r8, %r8
	je	.LBB1_193
# %bb.189:                              #   in Loop: Header=BB1_108 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB1_191
# %bb.190:                              #   in Loop: Header=BB1_108 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB1_193
.LBB1_191:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB1_193:                              #   in Loop: Header=BB1_108 Depth=1
	movq	%rbx, 8(%r12)
	movq	(%r12), %rax
	movb	$0, (%rax,%rbx)
	movq	(%r12), %rax
	movq	8(%r12), %rbp
	leaq	1(%rbp), %rbx
	movl	$15, %ecx
	cmpq	8(%rsp), %rax           # 8-byte Folded Reload
	je	.LBB1_195
# %bb.194:                              #   in Loop: Header=BB1_108 Depth=1
	movq	16(%r12), %rcx
.LBB1_195:                              #   in Loop: Header=BB1_108 Depth=1
	cmpq	%rcx, %rbx
	jbe	.LBB1_198
# %bb.196:                              #   in Loop: Header=BB1_108 Depth=1
.Ltmp46:
	movl	$1, %r8d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp47:
	jmp	.LBB1_197
.LBB1_199:
	movq	8(%r12), %rax
	testq	%rax, %rax
	je	.LBB1_201
# %bb.200:
	leaq	-1(%rax), %rcx
	movq	%rcx, 8(%r12)
	movq	(%r12), %rcx
	movb	$0, -1(%rcx,%rax)
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
.LBB1_201:
	cmpq	%rbp, %rbx
	jne	.LBB1_202
# %bb.206:
	testq	%rbp, %rbp
	je	.LBB1_208
.LBB1_207:
	movq	%rbp, %rdi
	callq	_ZdlPv
.LBB1_208:
	movq	88(%rsp), %rbp
	movq	96(%rsp), %rbx
	cmpq	%rbx, %rbp
	jne	.LBB1_209
# %bb.213:
	testq	%rbp, %rbp
	je	.LBB1_215
.LBB1_214:
	movq	%rbp, %rdi
	callq	_ZdlPv
.LBB1_215:
	movq	%r12, %rax
	addq	$136, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
	.p2align	4, 0x90
.LBB1_204:                              #   in Loop: Header=BB1_202 Depth=1
	.cfi_def_cfa_offset 192
	addq	$16, %rbx
	cmpq	%rbp, %rbx
	je	.LBB1_205
.LBB1_202:                              # =>This Inner Loop Header: Depth=1
	movq	(%rbx), %rdi
	addq	$16, %rbx
	cmpq	%rbx, %rdi
	je	.LBB1_204
# %bb.203:                              #   in Loop: Header=BB1_202 Depth=1
	callq	_ZdlPv
	jmp	.LBB1_204
	.p2align	4, 0x90
.LBB1_211:                              #   in Loop: Header=BB1_209 Depth=1
	addq	$16, %rbp
	cmpq	%rbx, %rbp
	je	.LBB1_212
.LBB1_209:                              # =>This Inner Loop Header: Depth=1
	movq	(%rbp), %rdi
	addq	$16, %rbp
	cmpq	%rbp, %rdi
	je	.LBB1_211
# %bb.210:                              #   in Loop: Header=BB1_209 Depth=1
	callq	_ZdlPv
	jmp	.LBB1_211
.LBB1_205:
	movq	56(%rsp), %rbp
	testq	%rbp, %rbp
	jne	.LBB1_207
	jmp	.LBB1_208
.LBB1_212:
	movq	88(%rsp), %rbp
	testq	%rbp, %rbp
	jne	.LBB1_214
	jmp	.LBB1_215
.LBB1_5:
	subq	%rcx, %rdx
	xorl	%ebx, %ebx
	jmp	.LBB1_6
	.p2align	4, 0x90
.LBB1_22:                               #   in Loop: Header=BB1_6 Depth=1
	addq	$256, %rax              # imm = 0x100
	addq	$-8, %rdx
	je	.LBB1_23
.LBB1_6:                                # =>This Inner Loop Header: Depth=1
	movq	8(%rax), %rdi
	movq	40(%rax), %rsi
	cmpq	%rdi, %rbx
	jae	.LBB1_7
# %bb.8:                                #   in Loop: Header=BB1_6 Depth=1
	cmpq	%rsi, %rdi
	jae	.LBB1_9
.LBB1_10:                               #   in Loop: Header=BB1_6 Depth=1
	movq	72(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_11
.LBB1_12:                               #   in Loop: Header=BB1_6 Depth=1
	movq	104(%rax), %rsi
	cmpq	%rsi, %rdi
	jae	.LBB1_13
.LBB1_14:                               #   in Loop: Header=BB1_6 Depth=1
	movq	136(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_15
.LBB1_16:                               #   in Loop: Header=BB1_6 Depth=1
	movq	168(%rax), %rsi
	cmpq	%rsi, %rdi
	jae	.LBB1_17
.LBB1_18:                               #   in Loop: Header=BB1_6 Depth=1
	movq	200(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_19
.LBB1_20:                               #   in Loop: Header=BB1_6 Depth=1
	movq	232(%rax), %rbx
	cmpq	%rbx, %rdi
	jb	.LBB1_22
	jmp	.LBB1_21
	.p2align	4, 0x90
.LBB1_7:                                #   in Loop: Header=BB1_6 Depth=1
	movq	%rbx, %rdi
	cmpq	%rsi, %rdi
	jb	.LBB1_10
.LBB1_9:                                #   in Loop: Header=BB1_6 Depth=1
	movq	%rdi, %rsi
	movq	72(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_12
.LBB1_11:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rsi, %rdi
	movq	104(%rax), %rsi
	cmpq	%rsi, %rdi
	jb	.LBB1_14
.LBB1_13:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rdi, %rsi
	movq	136(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_16
.LBB1_15:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rsi, %rdi
	movq	168(%rax), %rsi
	cmpq	%rsi, %rdi
	jb	.LBB1_18
.LBB1_17:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rdi, %rsi
	movq	200(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_20
.LBB1_19:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rsi, %rdi
	movq	232(%rax), %rbx
	cmpq	%rbx, %rdi
	jb	.LBB1_22
.LBB1_21:                               #   in Loop: Header=BB1_6 Depth=1
	movq	%rdi, %rbx
	jmp	.LBB1_22
.LBB1_30:
	subq	%rcx, %rdx
	xorl	%r13d, %r13d
	jmp	.LBB1_31
	.p2align	4, 0x90
.LBB1_47:                               #   in Loop: Header=BB1_31 Depth=1
	addq	$256, %rax              # imm = 0x100
	addq	$-8, %rdx
	je	.LBB1_48
.LBB1_31:                               # =>This Inner Loop Header: Depth=1
	movq	8(%rax), %rdi
	movq	40(%rax), %rsi
	cmpq	%rdi, %r13
	jae	.LBB1_32
# %bb.33:                               #   in Loop: Header=BB1_31 Depth=1
	cmpq	%rsi, %rdi
	jae	.LBB1_34
.LBB1_35:                               #   in Loop: Header=BB1_31 Depth=1
	movq	72(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_36
.LBB1_37:                               #   in Loop: Header=BB1_31 Depth=1
	movq	104(%rax), %rsi
	cmpq	%rsi, %rdi
	jae	.LBB1_38
.LBB1_39:                               #   in Loop: Header=BB1_31 Depth=1
	movq	136(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_40
.LBB1_41:                               #   in Loop: Header=BB1_31 Depth=1
	movq	168(%rax), %rsi
	cmpq	%rsi, %rdi
	jae	.LBB1_42
.LBB1_43:                               #   in Loop: Header=BB1_31 Depth=1
	movq	200(%rax), %rdi
	cmpq	%rdi, %rsi
	jae	.LBB1_44
.LBB1_45:                               #   in Loop: Header=BB1_31 Depth=1
	movq	232(%rax), %r13
	cmpq	%r13, %rdi
	jb	.LBB1_47
	jmp	.LBB1_46
	.p2align	4, 0x90
.LBB1_32:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%r13, %rdi
	cmpq	%rsi, %rdi
	jb	.LBB1_35
.LBB1_34:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rdi, %rsi
	movq	72(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_37
.LBB1_36:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rsi, %rdi
	movq	104(%rax), %rsi
	cmpq	%rsi, %rdi
	jb	.LBB1_39
.LBB1_38:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rdi, %rsi
	movq	136(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_41
.LBB1_40:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rsi, %rdi
	movq	168(%rax), %rsi
	cmpq	%rsi, %rdi
	jb	.LBB1_43
.LBB1_42:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rdi, %rsi
	movq	200(%rax), %rdi
	cmpq	%rdi, %rsi
	jb	.LBB1_45
.LBB1_44:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rsi, %rdi
	movq	232(%rax), %r13
	cmpq	%r13, %rdi
	jb	.LBB1_47
.LBB1_46:                               #   in Loop: Header=BB1_31 Depth=1
	movq	%rdi, %r13
	jmp	.LBB1_47
.LBB1_65:
.Ltmp7:
	movl	$.L.str.6, %edi
	movq	%r14, %rsi
	movq	%rcx, %rdx
	xorl	%eax, %eax
	callq	_ZSt24__throw_out_of_range_fmtPKcz
.Ltmp8:
# %bb.66:
.LBB1_84:
.Ltmp13:
	movl	$.L.str.6, %edi
	movq	%r14, %rsi
	xorl	%eax, %eax
	callq	_ZSt24__throw_out_of_range_fmtPKcz
.Ltmp14:
# %bb.85:
.LBB1_183:
.Ltmp41:
	movl	$.L.str.6, %edi
	movq	%r14, %rsi
	xorl	%eax, %eax
	callq	_ZSt24__throw_out_of_range_fmtPKcz
.Ltmp42:
# %bb.184:
.LBB1_123:
.Ltmp56:
	movl	$.L.str.4, %edi
	callq	_ZSt20__throw_length_errorPKc
.Ltmp57:
# %bb.124:
.LBB1_126:
.Ltmp54:
	callq	_ZSt17__throw_bad_allocv
.Ltmp55:
# %bb.127:
.LBB1_110:
.Ltmp51:
	movl	$.L.str.4, %edi
	callq	_ZSt20__throw_length_errorPKc
.Ltmp52:
# %bb.154:
.LBB1_156:
.Ltmp49:
	callq	_ZSt17__throw_bad_allocv
.Ltmp50:
# %bb.157:
.LBB1_217:
.Ltmp53:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_151:
.Ltmp58:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_231:
.Ltmp2:
	movq	%rax, %r14
	movq	88(%rsp), %rbx
	movq	96(%rsp), %rbp
	cmpq	%rbp, %rbx
	jne	.LBB1_233
	jmp	.LBB1_237
.LBB1_103:
.Ltmp43:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_219:
.Ltmp38:
	jmp	.LBB1_220
.LBB1_216:
.Ltmp35:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_153:
.Ltmp29:
.LBB1_220:
	movq	%rax, %r14
	movq	24(%rsp), %rdi
	leaq	40(%rsp), %rax
	cmpq	%rax, %rdi
	jne	.LBB1_221
# %bb.222:
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	jne	.LBB1_223
.LBB1_224:
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
	cmpq	%rbp, %rbx
	jne	.LBB1_225
.LBB1_229:
	testq	%rbx, %rbx
	jne	.LBB1_230
.LBB1_232:
	movq	88(%rsp), %rbx
	movq	96(%rsp), %rbp
	cmpq	%rbp, %rbx
	jne	.LBB1_233
.LBB1_237:
	testq	%rbx, %rbx
	jne	.LBB1_238
.LBB1_239:
	movq	%r14, %rdi
	callq	_Unwind_Resume
.LBB1_221:
	callq	_ZdlPv
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_150:
.Ltmp26:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_100:
.Ltmp48:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_101:
.Ltmp32:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
	jmp	.LBB1_223
.LBB1_102:
.Ltmp19:
	movq	%rax, %r14
	movq	(%r12), %rdi
	cmpq	8(%rsp), %rdi           # 8-byte Folded Reload
	je	.LBB1_224
.LBB1_223:
	callq	_ZdlPv
	movq	56(%rsp), %rbx
	movq	64(%rsp), %rbp
	cmpq	%rbp, %rbx
	je	.LBB1_229
.LBB1_225:                              # =>This Inner Loop Header: Depth=1
	movq	(%rbx), %rdi
	addq	$16, %rbx
	cmpq	%rbx, %rdi
	je	.LBB1_227
# %bb.226:                              #   in Loop: Header=BB1_225 Depth=1
	callq	_ZdlPv
.LBB1_227:                              #   in Loop: Header=BB1_225 Depth=1
	addq	$16, %rbx
	cmpq	%rbp, %rbx
	jne	.LBB1_225
# %bb.228:
	movq	56(%rsp), %rbx
	testq	%rbx, %rbx
	je	.LBB1_232
.LBB1_230:
	movq	%rbx, %rdi
	callq	_ZdlPv
	movq	88(%rsp), %rbx
	movq	96(%rsp), %rbp
	cmpq	%rbp, %rbx
	je	.LBB1_237
.LBB1_233:                              # =>This Inner Loop Header: Depth=1
	movq	(%rbx), %rdi
	addq	$16, %rbx
	cmpq	%rbx, %rdi
	je	.LBB1_235
# %bb.234:                              #   in Loop: Header=BB1_233 Depth=1
	callq	_ZdlPv
.LBB1_235:                              #   in Loop: Header=BB1_233 Depth=1
	addq	$16, %rbx
	cmpq	%rbp, %rbx
	jne	.LBB1_233
# %bb.236:
	movq	88(%rsp), %rbx
	testq	%rbx, %rbx
	je	.LBB1_239
.LBB1_238:
	movq	%rbx, %rdi
	callq	_ZdlPv
	movq	%r14, %rdi
	callq	_Unwind_Resume
.Lfunc_end1:
	.size	_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c, .Lfunc_end1-_ZN11cohen_chess4util15HorizontalMergeERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES8_S8_c
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table1:
.Lexception0:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end0-.Lcst_begin0
.Lcst_begin0:
	.uleb128 .Lfunc_begin0-.Lfunc_begin0 # >> Call Site 1 <<
	.uleb128 .Ltmp0-.Lfunc_begin0   #   Call between .Lfunc_begin0 and .Ltmp0
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp0-.Lfunc_begin0   # >> Call Site 2 <<
	.uleb128 .Ltmp1-.Ltmp0          #   Call between .Ltmp0 and .Ltmp1
	.uleb128 .Ltmp2-.Lfunc_begin0   #     jumps to .Ltmp2
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp3-.Lfunc_begin0   # >> Call Site 3 <<
	.uleb128 .Ltmp6-.Ltmp3          #   Call between .Ltmp3 and .Ltmp6
	.uleb128 .Ltmp43-.Lfunc_begin0  #     jumps to .Ltmp43
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp9-.Lfunc_begin0   # >> Call Site 4 <<
	.uleb128 .Ltmp10-.Ltmp9         #   Call between .Ltmp9 and .Ltmp10
	.uleb128 .Ltmp19-.Lfunc_begin0  #     jumps to .Ltmp19
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp10-.Lfunc_begin0  # >> Call Site 5 <<
	.uleb128 .Ltmp11-.Ltmp10        #   Call between .Ltmp10 and .Ltmp11
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp11-.Lfunc_begin0  # >> Call Site 6 <<
	.uleb128 .Ltmp12-.Ltmp11        #   Call between .Ltmp11 and .Ltmp12
	.uleb128 .Ltmp19-.Lfunc_begin0  #     jumps to .Ltmp19
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp12-.Lfunc_begin0  # >> Call Site 7 <<
	.uleb128 .Ltmp15-.Ltmp12        #   Call between .Ltmp12 and .Ltmp15
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp15-.Lfunc_begin0  # >> Call Site 8 <<
	.uleb128 .Ltmp16-.Ltmp15        #   Call between .Ltmp15 and .Ltmp16
	.uleb128 .Ltmp19-.Lfunc_begin0  #     jumps to .Ltmp19
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp16-.Lfunc_begin0  # >> Call Site 9 <<
	.uleb128 .Ltmp17-.Ltmp16        #   Call between .Ltmp16 and .Ltmp17
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp17-.Lfunc_begin0  # >> Call Site 10 <<
	.uleb128 .Ltmp18-.Ltmp17        #   Call between .Ltmp17 and .Ltmp18
	.uleb128 .Ltmp19-.Lfunc_begin0  #     jumps to .Ltmp19
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp20-.Lfunc_begin0  # >> Call Site 11 <<
	.uleb128 .Ltmp21-.Ltmp20        #   Call between .Ltmp20 and .Ltmp21
	.uleb128 .Ltmp32-.Lfunc_begin0  #     jumps to .Ltmp32
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp21-.Lfunc_begin0  # >> Call Site 12 <<
	.uleb128 .Ltmp22-.Ltmp21        #   Call between .Ltmp21 and .Ltmp22
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp22-.Lfunc_begin0  # >> Call Site 13 <<
	.uleb128 .Ltmp23-.Ltmp22        #   Call between .Ltmp22 and .Ltmp23
	.uleb128 .Ltmp32-.Lfunc_begin0  #     jumps to .Ltmp32
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp23-.Lfunc_begin0  # >> Call Site 14 <<
	.uleb128 .Ltmp24-.Ltmp23        #   Call between .Ltmp23 and .Ltmp24
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp24-.Lfunc_begin0  # >> Call Site 15 <<
	.uleb128 .Ltmp25-.Ltmp24        #   Call between .Ltmp24 and .Ltmp25
	.uleb128 .Ltmp26-.Lfunc_begin0  #     jumps to .Ltmp26
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp25-.Lfunc_begin0  # >> Call Site 16 <<
	.uleb128 .Ltmp27-.Ltmp25        #   Call between .Ltmp25 and .Ltmp27
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp27-.Lfunc_begin0  # >> Call Site 17 <<
	.uleb128 .Ltmp28-.Ltmp27        #   Call between .Ltmp27 and .Ltmp28
	.uleb128 .Ltmp29-.Lfunc_begin0  #     jumps to .Ltmp29
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp28-.Lfunc_begin0  # >> Call Site 18 <<
	.uleb128 .Ltmp30-.Ltmp28        #   Call between .Ltmp28 and .Ltmp30
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp30-.Lfunc_begin0  # >> Call Site 19 <<
	.uleb128 .Ltmp31-.Ltmp30        #   Call between .Ltmp30 and .Ltmp31
	.uleb128 .Ltmp32-.Lfunc_begin0  #     jumps to .Ltmp32
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp33-.Lfunc_begin0  # >> Call Site 20 <<
	.uleb128 .Ltmp34-.Ltmp33        #   Call between .Ltmp33 and .Ltmp34
	.uleb128 .Ltmp35-.Lfunc_begin0  #     jumps to .Ltmp35
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp34-.Lfunc_begin0  # >> Call Site 21 <<
	.uleb128 .Ltmp36-.Ltmp34        #   Call between .Ltmp34 and .Ltmp36
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp36-.Lfunc_begin0  # >> Call Site 22 <<
	.uleb128 .Ltmp37-.Ltmp36        #   Call between .Ltmp36 and .Ltmp37
	.uleb128 .Ltmp38-.Lfunc_begin0  #     jumps to .Ltmp38
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp37-.Lfunc_begin0  # >> Call Site 23 <<
	.uleb128 .Ltmp39-.Ltmp37        #   Call between .Ltmp37 and .Ltmp39
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp39-.Lfunc_begin0  # >> Call Site 24 <<
	.uleb128 .Ltmp40-.Ltmp39        #   Call between .Ltmp39 and .Ltmp40
	.uleb128 .Ltmp48-.Lfunc_begin0  #     jumps to .Ltmp48
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp40-.Lfunc_begin0  # >> Call Site 25 <<
	.uleb128 .Ltmp44-.Ltmp40        #   Call between .Ltmp40 and .Ltmp44
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp44-.Lfunc_begin0  # >> Call Site 26 <<
	.uleb128 .Ltmp45-.Ltmp44        #   Call between .Ltmp44 and .Ltmp45
	.uleb128 .Ltmp48-.Lfunc_begin0  #     jumps to .Ltmp48
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp45-.Lfunc_begin0  # >> Call Site 27 <<
	.uleb128 .Ltmp46-.Ltmp45        #   Call between .Ltmp45 and .Ltmp46
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp46-.Lfunc_begin0  # >> Call Site 28 <<
	.uleb128 .Ltmp47-.Ltmp46        #   Call between .Ltmp46 and .Ltmp47
	.uleb128 .Ltmp48-.Lfunc_begin0  #     jumps to .Ltmp48
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp7-.Lfunc_begin0   # >> Call Site 29 <<
	.uleb128 .Ltmp42-.Ltmp7         #   Call between .Ltmp7 and .Ltmp42
	.uleb128 .Ltmp43-.Lfunc_begin0  #     jumps to .Ltmp43
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp56-.Lfunc_begin0  # >> Call Site 30 <<
	.uleb128 .Ltmp55-.Ltmp56        #   Call between .Ltmp56 and .Ltmp55
	.uleb128 .Ltmp58-.Lfunc_begin0  #     jumps to .Ltmp58
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp51-.Lfunc_begin0  # >> Call Site 31 <<
	.uleb128 .Ltmp50-.Ltmp51        #   Call between .Ltmp51 and .Ltmp50
	.uleb128 .Ltmp53-.Lfunc_begin0  #     jumps to .Ltmp53
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp50-.Lfunc_begin0  # >> Call Site 32 <<
	.uleb128 .Lfunc_end1-.Ltmp50    #   Call between .Ltmp50 and .Lfunc_end1
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end0:
	.p2align	2
                                        # -- End function
	.section	.text._ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc,"axG",@progbits,_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc,comdat
	.weak	_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc # -- Begin function _ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc
	.p2align	4, 0x90
	.type	_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc,@function
_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc: # @_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc
.Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception1
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movl	%edx, 8(%rsp)           # 4-byte Spill
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%rdi), %rbx
	cmpq	%rbx, 8(%rdi)
	jne	.LBB2_1
.LBB2_27:
	addq	$56, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB2_1:
	.cfi_def_cfa_offset 112
	movq	%rdi, %r13
	xorl	%r12d, %r12d
	movzbl	8(%rsp), %eax           # 1-byte Folded Reload
	movl	%eax, 12(%rsp)          # 4-byte Spill
	xorl	%r15d, %r15d
	jmp	.LBB2_2
	.p2align	4, 0x90
.LBB2_26:                               #   in Loop: Header=BB2_2 Depth=1
	addq	$1, %r15
	movq	(%r13), %rbx
	movq	8(%r13), %rax
	subq	%rbx, %rax
	sarq	$5, %rax
	addq	$32, %r12
	cmpq	%rax, %r15
	jae	.LBB2_27
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	movq	48(%rsp), %rbp          # 8-byte Reload
	subq	8(%rbx,%r12), %rbp
	leaq	32(%rsp), %rax
	movq	%rax, 16(%rsp)
	cmpq	$16, %rbp
	jb	.LBB2_12
# %bb.3:                                #   in Loop: Header=BB2_2 Depth=1
	testq	%rbp, %rbp
	js	.LBB2_4
# %bb.6:                                #   in Loop: Header=BB2_2 Depth=1
	movq	%rbp, %rdi
	incq	%rdi
	js	.LBB2_7
# %bb.9:                                #   in Loop: Header=BB2_2 Depth=1
.Ltmp59:
	callq	_Znwm
.Ltmp60:
# %bb.10:                               #   in Loop: Header=BB2_2 Depth=1
	movq	%rax, %r14
	movq	%rax, 16(%rsp)
	movq	%rbp, 32(%rsp)
	jmp	.LBB2_11
	.p2align	4, 0x90
.LBB2_12:                               #   in Loop: Header=BB2_2 Depth=1
	leaq	32(%rsp), %r14
	testq	%rbp, %rbp
	je	.LBB2_15
# %bb.13:                               #   in Loop: Header=BB2_2 Depth=1
	cmpq	$1, %rbp
	jne	.LBB2_11
# %bb.14:                               #   in Loop: Header=BB2_2 Depth=1
	movl	8(%rsp), %eax           # 4-byte Reload
	movb	%al, 32(%rsp)
	leaq	32(%rsp), %r14
	jmp	.LBB2_15
	.p2align	4, 0x90
.LBB2_11:                               #   in Loop: Header=BB2_2 Depth=1
	movq	%r14, %rdi
	movl	12(%rsp), %esi          # 4-byte Reload
	movq	%rbp, %rdx
	callq	memset
.LBB2_15:                               #   in Loop: Header=BB2_2 Depth=1
	movq	%rbp, 24(%rsp)
	movb	$0, (%r14,%rbp)
	movq	16(%rsp), %rcx
	movq	24(%rsp), %r8
	movq	(%rbx,%r12), %rdi
	movq	8(%rbx,%r12), %rsi
	leaq	(%rsi,%r8), %rbp
	leaq	(%rbx,%r12), %rax
	addq	$16, %rax
	cmpq	%rdi, %rax
	je	.LBB2_16
# %bb.17:                               #   in Loop: Header=BB2_2 Depth=1
	movq	16(%rbx,%r12), %rax
	addq	%r12, %rbx
	cmpq	%rax, %rbp
	jbe	.LBB2_19
.LBB2_23:                               #   in Loop: Header=BB2_2 Depth=1
.Ltmp62:
	movq	%rbx, %rdi
	xorl	%edx, %edx
	callq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.Ltmp63:
	jmp	.LBB2_24
	.p2align	4, 0x90
.LBB2_16:                               #   in Loop: Header=BB2_2 Depth=1
	movl	$15, %eax
	addq	%r12, %rbx
	cmpq	%rax, %rbp
	ja	.LBB2_23
.LBB2_19:                               #   in Loop: Header=BB2_2 Depth=1
	testq	%r8, %r8
	je	.LBB2_24
# %bb.20:                               #   in Loop: Header=BB2_2 Depth=1
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.LBB2_22
# %bb.21:                               #   in Loop: Header=BB2_2 Depth=1
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.LBB2_24
.LBB2_22:                               #   in Loop: Header=BB2_2 Depth=1
	movq	%rcx, %rsi
	movq	%r8, %rdx
	callq	memcpy
	.p2align	4, 0x90
.LBB2_24:                               #   in Loop: Header=BB2_2 Depth=1
	movq	%rbp, 8(%rbx)
	movq	(%rbx), %rax
	movb	$0, (%rax,%rbp)
	movq	16(%rsp), %rdi
	leaq	32(%rsp), %rax
	cmpq	%rax, %rdi
	je	.LBB2_26
# %bb.25:                               #   in Loop: Header=BB2_2 Depth=1
	callq	_ZdlPv
	jmp	.LBB2_26
.LBB2_7:
.Ltmp65:
	callq	_ZSt17__throw_bad_allocv
.Ltmp66:
# %bb.8:
.LBB2_4:
.Ltmp67:
	movl	$.L.str.4, %edi
	callq	_ZSt20__throw_length_errorPKc
.Ltmp68:
# %bb.5:
.LBB2_29:
.Ltmp69:
	movq	%rax, %rdi
	callq	_Unwind_Resume
.LBB2_28:
.Ltmp61:
	movq	%rax, %rdi
	callq	_Unwind_Resume
.LBB2_31:
.Ltmp64:
	movq	%rax, %rbx
	movq	16(%rsp), %rdi
	leaq	32(%rsp), %rax
	cmpq	%rax, %rdi
	je	.LBB2_33
# %bb.32:
	callq	_ZdlPv
.LBB2_33:
	movq	%rbx, %rdi
	callq	_Unwind_Resume
.Lfunc_end2:
	.size	_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc, .Lfunc_end2-_ZN11cohen_chess4util8PadRightERSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS7_EEmc
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table2:
.Lexception1:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end1-.Lcst_begin1
.Lcst_begin1:
	.uleb128 .Ltmp59-.Lfunc_begin1  # >> Call Site 1 <<
	.uleb128 .Ltmp60-.Ltmp59        #   Call between .Ltmp59 and .Ltmp60
	.uleb128 .Ltmp61-.Lfunc_begin1  #     jumps to .Ltmp61
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp60-.Lfunc_begin1  # >> Call Site 2 <<
	.uleb128 .Ltmp62-.Ltmp60        #   Call between .Ltmp60 and .Ltmp62
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp62-.Lfunc_begin1  # >> Call Site 3 <<
	.uleb128 .Ltmp63-.Ltmp62        #   Call between .Ltmp62 and .Ltmp63
	.uleb128 .Ltmp64-.Lfunc_begin1  #     jumps to .Ltmp64
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp63-.Lfunc_begin1  # >> Call Site 4 <<
	.uleb128 .Ltmp65-.Ltmp63        #   Call between .Ltmp63 and .Ltmp65
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp65-.Lfunc_begin1  # >> Call Site 5 <<
	.uleb128 .Ltmp68-.Ltmp65        #   Call between .Ltmp65 and .Ltmp68
	.uleb128 .Ltmp69-.Lfunc_begin1  #     jumps to .Ltmp69
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp68-.Lfunc_begin1  # >> Call Site 6 <<
	.uleb128 .Lfunc_end2-.Ltmp68    #   Call between .Ltmp68 and .Lfunc_end2
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end1:
	.p2align	2
                                        # -- End function
	.text
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%r12
	.cfi_def_cfa_offset 32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	subq	$136, %rsp
	.cfi_def_cfa_offset 176
	.cfi_offset %rbx, -40
	.cfi_offset %r12, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	leaq	1(%rsp), %r14
	xorl	%r12d, %r12d
	jmp	.LBB3_1
	.p2align	4, 0x90
.LBB3_6:                                #   in Loop: Header=BB3_1 Depth=1
	movq	%rbx, %rdi
	callq	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movq	%rbx, %rdi
	movl	$10, %esi
	callq	*48(%rax)
.LBB3_7:                                #   in Loop: Header=BB3_1 Depth=1
	movsbl	%al, %esi
	movq	%r15, %rdi
	callq	_ZNSo3putEc
	movq	%rax, %rdi
	callq	_ZNSo5flushEv
	addq	$1, %r12
	cmpq	$64, %r12
	je	.LBB3_8
.LBB3_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_2 Depth 2
	movq	_ZN11cohen_chess8bitboard9kRayTableILa8EEE(,%r12,8), %rax
	movb	$0, (%rsp)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+112(%rip), %xmm0
	movups	%xmm0, 112(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+96(%rip), %xmm0
	movups	%xmm0, 96(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+80(%rip), %xmm0
	movups	%xmm0, 80(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+64(%rip), %xmm0
	movups	%xmm0, 64(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+48(%rip), %xmm0
	movups	%xmm0, 48(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+32(%rip), %xmm0
	movups	%xmm0, 32(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE+16(%rip), %xmm0
	movups	%xmm0, 16(%r14)
	movups	_ZN11cohen_chess10AsciiBoard12kInitialDataE(%rip), %xmm0
	movups	%xmm0, (%r14)
	xorl	%edx, %edx
	testq	%rax, %rax
	je	.LBB3_3
	.p2align	4, 0x90
.LBB3_2:                                #   Parent Loop BB3_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	bsfq	%rax, %rsi
	leaq	-1(%rax), %r8
	movl	%esi, %ebx
	shrb	$3, %bl
	movzbl	%dl, %edx
	leal	(,%rdx,8), %edi
	subl	%edx, %edi
                                        # kill: def $dl killed $dl killed $rdx
	xorb	$1, %dl
	movzbl	%dl, %edx
	leal	(,%rdx,8), %ecx
	subl	%edx, %ecx
	xorb	%bl, %cl
	andb	$7, %sil
	xorb	%sil, %dil
	movsbl	%cl, %ecx
	shll	$4, %ecx
	movsbl	%dil, %edx
	leal	(%rcx,%rdx,2), %ecx
	movslq	%ecx, %rcx
	movb	$49, 1(%rsp,%rcx)
	movzbl	(%rsp), %edx
	andq	%r8, %rax
	jne	.LBB3_2
.LBB3_3:                                #   in Loop: Header=BB3_1 Depth=1
	movl	%r12d, %eax
	sarb	$3, %al
	movzbl	%dl, %ecx
	leal	(,%rcx,8), %edx
	subl	%ecx, %edx
                                        # kill: def $cl killed $cl killed $rcx
	xorb	$1, %cl
	movzbl	%cl, %ecx
	leal	(,%rcx,8), %esi
	subl	%ecx, %esi
	xorb	%al, %sil
	movl	%r12d, %eax
	andb	$7, %al
	xorb	%al, %dl
	movsbl	%sil, %eax
	shll	$4, %eax
	movsbl	%dl, %ecx
	leal	(%rax,%rcx,2), %eax
	cltq
	movb	$120, 1(%rsp,%rax)
	movl	$_ZSt4cout, %edi
	movl	$128, %edx
	movq	%r14, %rsi
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rax, %r15
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r15,%rax), %rbx
	testq	%rbx, %rbx
	je	.LBB3_9
# %bb.4:                                #   in Loop: Header=BB3_1 Depth=1
	cmpb	$0, 56(%rbx)
	je	.LBB3_6
# %bb.5:                                #   in Loop: Header=BB3_1 Depth=1
	movb	67(%rbx), %al
	jmp	.LBB3_7
.LBB3_8:
	xorl	%eax, %eax
	addq	$136, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.LBB3_9:
	.cfi_def_cfa_offset 176
	callq	_ZSt16__throw_bad_castv
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN11cohen_chess4util8TokenizeB5cxx11EPKcc,"axG",@progbits,_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc,comdat
	.weak	_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc # -- Begin function _ZN11cohen_chess4util8TokenizeB5cxx11EPKcc
	.p2align	4, 0x90
	.type	_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc,@function
_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc: # @_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc
.Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception2
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movl	%edx, %ebp
	movq	%rsi, %rbx
	movq	%rdi, %r12
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rdi)
	movq	$0, 16(%rdi)
	leaq	24(%rsp), %r13
	movq	%rdi, (%rsp)            # 8-byte Spill
	jmp	.LBB4_4
	.p2align	4, 0x90
.LBB4_1:                                #   in Loop: Header=BB4_4 Depth=1
	movq	%rcx, (%rsi)
	movq	24(%rsp), %rax
	movq	%rax, 16(%rsi)
.LBB4_2:                                #   in Loop: Header=BB4_4 Depth=1
	movq	16(%rsp), %rax
	movq	%rax, 8(%rsi)
	movq	%r13, 8(%rsp)
	movq	$0, 16(%rsp)
	movb	$0, 24(%rsp)
	addq	$32, 8(%r12)
.LBB4_3:                                #   in Loop: Header=BB4_4 Depth=1
	addq	%r15, %rbx
	cmpb	$0, (%r14)
	je	.LBB4_24
.LBB4_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB4_5 Depth 2
	xorl	%r15d, %r15d
	.p2align	4, 0x90
.LBB4_5:                                #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%rbx,%r15), %eax
	addq	$1, %r15
	cmpb	%bpl, %al
	je	.LBB4_7
# %bb.6:                                #   in Loop: Header=BB4_5 Depth=2
	testb	%al, %al
	jne	.LBB4_5
.LBB4_7:                                #   in Loop: Header=BB4_4 Depth=1
	movq	%r13, 8(%rsp)
	testq	%rbx, %rbx
	jne	.LBB4_9
# %bb.8:                                #   in Loop: Header=BB4_4 Depth=1
	cmpq	$1, %r15
	jne	.LBB4_25
.LBB4_9:                                #   in Loop: Header=BB4_4 Depth=1
	leaq	(%rbx,%r15), %r14
	addq	$-1, %r14
	movq	%r14, %r12
	subq	%rbx, %r12
	cmpq	$16, %r12
	jb	.LBB4_14
# %bb.10:                               #   in Loop: Header=BB4_4 Depth=1
	testq	%r12, %r12
	js	.LBB4_27
# %bb.11:                               #   in Loop: Header=BB4_4 Depth=1
	movq	%r12, %rdi
	incq	%rdi
	js	.LBB4_29
# %bb.12:                               #   in Loop: Header=BB4_4 Depth=1
.Ltmp72:
	callq	_Znwm
.Ltmp73:
# %bb.13:                               #   in Loop: Header=BB4_4 Depth=1
	movq	%rax, %r13
	movq	%rax, 8(%rsp)
	movq	%r12, 24(%rsp)
.LBB4_14:                               #   in Loop: Header=BB4_4 Depth=1
	testq	%r12, %r12
	je	.LBB4_18
# %bb.15:                               #   in Loop: Header=BB4_4 Depth=1
	cmpq	$1, %r12
	jne	.LBB4_17
# %bb.16:                               #   in Loop: Header=BB4_4 Depth=1
	movb	(%rbx), %al
	movb	%al, (%r13)
	jmp	.LBB4_18
	.p2align	4, 0x90
.LBB4_17:                               #   in Loop: Header=BB4_4 Depth=1
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movq	%r12, %rdx
	callq	memcpy
.LBB4_18:                               #   in Loop: Header=BB4_4 Depth=1
	movq	%r12, 16(%rsp)
	movb	$0, (%r13,%r12)
	movq	(%rsp), %r12            # 8-byte Reload
	movq	8(%r12), %rsi
	cmpq	16(%r12), %rsi
	je	.LBB4_21
# %bb.19:                               #   in Loop: Header=BB4_4 Depth=1
	leaq	16(%rsi), %rax
	movq	%rax, (%rsi)
	movq	8(%rsp), %rcx
	leaq	24(%rsp), %r13
	cmpq	%r13, %rcx
	jne	.LBB4_1
# %bb.20:                               #   in Loop: Header=BB4_4 Depth=1
	movups	(%r13), %xmm0
	movups	%xmm0, (%rax)
	jmp	.LBB4_2
	.p2align	4, 0x90
.LBB4_21:                               #   in Loop: Header=BB4_4 Depth=1
.Ltmp75:
	movq	%r12, %rdi
	leaq	8(%rsp), %rdx
	leaq	24(%rsp), %r13
	callq	_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_
.Ltmp76:
# %bb.22:                               #   in Loop: Header=BB4_4 Depth=1
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.LBB4_3
# %bb.23:                               #   in Loop: Header=BB4_4 Depth=1
	callq	_ZdlPv
	jmp	.LBB4_3
.LBB4_24:
	movq	%r12, %rax
	addq	$40, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB4_25:
	.cfi_def_cfa_offset 96
.Ltmp70:
	movl	$.L.str.3, %edi
	callq	_ZSt19__throw_logic_errorPKc
.Ltmp71:
# %bb.26:
.LBB4_27:
.Ltmp80:
	movl	$.L.str.4, %edi
	callq	_ZSt20__throw_length_errorPKc
.Ltmp81:
# %bb.28:
.LBB4_29:
.Ltmp78:
	callq	_ZSt17__throw_bad_allocv
.Ltmp79:
# %bb.30:
.LBB4_31:
.Ltmp82:
	jmp	.LBB4_35
.LBB4_32:
.Ltmp77:
	movq	%rax, %r14
	movq	8(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.LBB4_36
# %bb.33:
	callq	_ZdlPv
	jmp	.LBB4_36
.LBB4_34:
.Ltmp74:
.LBB4_35:
	movq	%rax, %r14
.LBB4_36:
	movq	(%rsp), %rax            # 8-byte Reload
	movq	(%rax), %rbp
	movq	8(%rax), %rbx
	cmpq	%rbx, %rbp
	jne	.LBB4_39
# %bb.37:
	testq	%rbp, %rbp
	jne	.LBB4_43
.LBB4_38:
	movq	%r14, %rdi
	callq	_Unwind_Resume
.LBB4_39:                               # =>This Inner Loop Header: Depth=1
	movq	(%rbp), %rdi
	addq	$16, %rbp
	cmpq	%rbp, %rdi
	je	.LBB4_41
# %bb.40:                               #   in Loop: Header=BB4_39 Depth=1
	callq	_ZdlPv
.LBB4_41:                               #   in Loop: Header=BB4_39 Depth=1
	addq	$16, %rbp
	cmpq	%rbx, %rbp
	jne	.LBB4_39
# %bb.42:
	movq	(%rsp), %rax            # 8-byte Reload
	movq	(%rax), %rbp
	testq	%rbp, %rbp
	je	.LBB4_38
.LBB4_43:
	movq	%rbp, %rdi
	callq	_ZdlPv
	movq	%r14, %rdi
	callq	_Unwind_Resume
.Lfunc_end4:
	.size	_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc, .Lfunc_end4-_ZN11cohen_chess4util8TokenizeB5cxx11EPKcc
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table4:
.Lexception2:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end2-.Lcst_begin2
.Lcst_begin2:
	.uleb128 .Ltmp72-.Lfunc_begin2  # >> Call Site 1 <<
	.uleb128 .Ltmp73-.Ltmp72        #   Call between .Ltmp72 and .Ltmp73
	.uleb128 .Ltmp74-.Lfunc_begin2  #     jumps to .Ltmp74
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp73-.Lfunc_begin2  # >> Call Site 2 <<
	.uleb128 .Ltmp75-.Ltmp73        #   Call between .Ltmp73 and .Ltmp75
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp75-.Lfunc_begin2  # >> Call Site 3 <<
	.uleb128 .Ltmp76-.Ltmp75        #   Call between .Ltmp75 and .Ltmp76
	.uleb128 .Ltmp77-.Lfunc_begin2  #     jumps to .Ltmp77
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp70-.Lfunc_begin2  # >> Call Site 4 <<
	.uleb128 .Ltmp79-.Ltmp70        #   Call between .Ltmp70 and .Ltmp79
	.uleb128 .Ltmp82-.Lfunc_begin2  #     jumps to .Ltmp82
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp79-.Lfunc_begin2  # >> Call Site 5 <<
	.uleb128 .Lfunc_end4-.Ltmp79    #   Call between .Ltmp79 and .Lfunc_end4
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end2:
	.p2align	2
                                        # -- End function
	.section	.text._ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_,"axG",@progbits,_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_,comdat
	.weak	_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_ # -- Begin function _ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_
	.p2align	4, 0x90
	.type	_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_,@function
_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_: # @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rsi, %rbx
	movq	(%rdi), %rsi
	movq	8(%rdi), %r14
	movq	%r14, %rax
	subq	%rsi, %rax
	movabsq	$9223372036854775776, %rcx # imm = 0x7FFFFFFFFFFFFFE0
	cmpq	%rcx, %rax
	je	.LBB5_25
# %bb.1:
	movq	%rdx, %r13
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	movq	%rax, %rcx
	sarq	$5, %rcx
	testq	%rax, %rax
	movl	$1, %eax
	cmovneq	%rcx, %rax
	leaq	(%rax,%rcx), %r15
	movq	%r15, %rdx
	shrq	$58, %rdx
	movabsq	$288230376151711743, %rdx # imm = 0x3FFFFFFFFFFFFFF
	cmovneq	%rdx, %r15
	addq	%rcx, %rax
	cmovbq	%rdx, %r15
	movq	%rbx, %rbp
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	subq	%rsi, %rbp
	sarq	$5, %rbp
	testq	%r15, %r15
	je	.LBB5_2
# %bb.3:
	movq	%r15, %rdi
	shlq	$5, %rdi
	callq	_Znwm
	movq	%rax, %r12
	jmp	.LBB5_4
.LBB5_2:
	xorl	%r12d, %r12d
.LBB5_4:
	shlq	$5, %rbp
	leaq	(%r12,%rbp), %rcx
	addq	$16, %rcx
	movq	%rcx, (%r12,%rbp)
	movq	(%r13), %rdx
	leaq	16(%r13), %rax
	cmpq	%rax, %rdx
	je	.LBB5_5
# %bb.6:
	leaq	(%r12,%rbp), %rcx
	movq	%rdx, (%rcx)
	movq	16(%r13), %rcx
	movq	%rcx, 16(%r12,%rbp)
	jmp	.LBB5_7
.LBB5_5:
	movups	(%rdx), %xmm0
	movups	%xmm0, (%rcx)
.LBB5_7:
	movq	8(%rsp), %rdi           # 8-byte Reload
	movq	8(%r13), %rcx
	movq	%rcx, 8(%r12,%rbp)
	movq	%rax, (%r13)
	movq	$0, 8(%r13)
	movb	$0, 16(%r13)
	movq	%r12, %rbp
	cmpq	%rbx, %rdi
	je	.LBB5_14
# %bb.8:
	leaq	16(%r12), %rbp
	leaq	16(%rdi), %rax
	jmp	.LBB5_9
	.p2align	4, 0x90
.LBB5_11:                               #   in Loop: Header=BB5_9 Depth=1
	movq	%rcx, -16(%rbp)
	movq	(%rax), %rcx
	movq	%rcx, (%rbp)
.LBB5_12:                               #   in Loop: Header=BB5_9 Depth=1
	movq	-8(%rax), %rcx
	movq	%rcx, -8(%rbp)
	movq	%rax, -16(%rax)
	movq	$0, -8(%rax)
	movb	$0, (%rax)
	addq	$32, %rbp
	leaq	32(%rax), %rcx
	addq	$16, %rax
	cmpq	%rbx, %rax
	movq	%rcx, %rax
	je	.LBB5_13
.LBB5_9:                                # =>This Inner Loop Header: Depth=1
	movq	%rbp, -16(%rbp)
	movq	-16(%rax), %rcx
	cmpq	%rax, %rcx
	jne	.LBB5_11
# %bb.10:                               #   in Loop: Header=BB5_9 Depth=1
	movups	(%rcx), %xmm0
	movups	%xmm0, (%rbp)
	jmp	.LBB5_12
.LBB5_13:
	addq	$-16, %rbp
.LBB5_14:
	cmpq	%rbx, %r14
	je	.LBB5_15
# %bb.16:
	addq	$48, %rbp
	addq	$16, %rbx
	jmp	.LBB5_17
	.p2align	4, 0x90
.LBB5_19:                               #   in Loop: Header=BB5_17 Depth=1
	movq	%rax, -16(%rbp)
	movq	(%rbx), %rax
	movq	%rax, (%rbp)
.LBB5_20:                               #   in Loop: Header=BB5_17 Depth=1
	movq	-8(%rbx), %rax
	movq	%rax, -8(%rbp)
	movq	%rbx, -16(%rbx)
	movq	$0, -8(%rbx)
	movb	$0, (%rbx)
	addq	$32, %rbp
	leaq	32(%rbx), %rax
	addq	$16, %rbx
	cmpq	%r14, %rbx
	movq	%rax, %rbx
	je	.LBB5_21
.LBB5_17:                               # =>This Inner Loop Header: Depth=1
	movq	%rbp, -16(%rbp)
	movq	-16(%rbx), %rax
	cmpq	%rbx, %rax
	jne	.LBB5_19
# %bb.18:                               #   in Loop: Header=BB5_17 Depth=1
	movups	(%rax), %xmm0
	movups	%xmm0, (%rbp)
	jmp	.LBB5_20
.LBB5_21:
	addq	$-16, %rbp
	testq	%rdi, %rdi
	je	.LBB5_24
.LBB5_23:
	callq	_ZdlPv
.LBB5_24:
	movq	16(%rsp), %rax          # 8-byte Reload
	movq	%r12, (%rax)
	movq	%rbp, 8(%rax)
	shlq	$5, %r15
	addq	%r12, %r15
	movq	%r15, 16(%rax)
	addq	$24, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB5_15:
	.cfi_def_cfa_offset 80
	addq	$32, %rbp
	testq	%rdi, %rdi
	jne	.LBB5_23
	jmp	.LBB5_24
.LBB5_25:
	movl	$.L.str.2, %edi
	callq	_ZSt20__throw_length_errorPKc
.Lfunc_end5:
	.size	_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_, .Lfunc_end5-_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_insertIJS5_EEEvN9__gnu_cxx17__normal_iteratorIPS5_S7_EEDpOT_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,comdat
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm # -- Begin function _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.p2align	4, 0x90
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,@function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm: # @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%r8, %rbp
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbx
	movq	%rdi, %r14
	movq	8(%rdi), %r15
	movq	%r8, %r13
	movq	%rdx, (%rsp)            # 8-byte Spill
	subq	%rdx, %r13
	addq	%r15, %r13
	leaq	16(%rdi), %rcx
	cmpq	%rcx, (%rdi)
	je	.LBB6_1
# %bb.2:
	movq	16(%r14), %rax
	testq	%r13, %r13
	js	.LBB6_25
.LBB6_4:
	cmpq	%rax, %r13
	jbe	.LBB6_7
# %bb.5:
	addq	%rax, %rax
	cmpq	%rax, %r13
	jae	.LBB6_7
# %bb.6:
	movabsq	$9223372036854775807, %r13 # imm = 0x7FFFFFFFFFFFFFFF
	cmpq	%r13, %rax
	cmovbq	%rax, %r13
.LBB6_7:
	movq	%rcx, 16(%rsp)          # 8-byte Spill
	movq	%r13, %rdi
	incq	%rdi
	js	.LBB6_26
# %bb.8:
	subq	%rbx, %r15
	callq	_Znwm
	movq	%rax, %r12
	testq	%rbx, %rbx
	je	.LBB6_12
# %bb.9:
	movq	(%r14), %rsi
	cmpq	$1, %rbx
	jne	.LBB6_11
# %bb.10:
	movb	(%rsi), %al
	movb	%al, (%r12)
.LBB6_12:
	subq	(%rsp), %r15            # 8-byte Folded Reload
	movq	8(%rsp), %rsi           # 8-byte Reload
	testq	%rsi, %rsi
	jne	.LBB6_13
	jmp	.LBB6_17
.LBB6_1:
	movl	$15, %eax
	testq	%r13, %r13
	jns	.LBB6_4
.LBB6_25:
	movl	$.L.str.4, %edi
	callq	_ZSt20__throw_length_errorPKc
.LBB6_11:
	movq	%r12, %rdi
	movq	%rbx, %rdx
	callq	memcpy
	subq	(%rsp), %r15            # 8-byte Folded Reload
	movq	8(%rsp), %rsi           # 8-byte Reload
	testq	%rsi, %rsi
	je	.LBB6_17
.LBB6_13:
	testq	%rbp, %rbp
	je	.LBB6_17
# %bb.14:
	leaq	(%r12,%rbx), %rdi
	cmpq	$1, %rbp
	jne	.LBB6_16
# %bb.15:
	movb	(%rsi), %al
	movb	%al, (%rdi)
.LBB6_17:
	testq	%r15, %r15
	je	.LBB6_18
.LBB6_19:
	movq	%r12, %rdi
	addq	%rbx, %rdi
	addq	%rbp, %rdi
	movq	(%r14), %rbp
	addq	%rbp, %rbx
	addq	(%rsp), %rbx            # 8-byte Folded Reload
	cmpq	$1, %r15
	jne	.LBB6_21
# %bb.20:
	movb	(%rbx), %al
	movb	%al, (%rdi)
	cmpq	16(%rsp), %rbp          # 8-byte Folded Reload
	jne	.LBB6_23
	jmp	.LBB6_24
.LBB6_21:
	movq	%rbx, %rsi
	movq	%r15, %rdx
	callq	memcpy
	cmpq	16(%rsp), %rbp          # 8-byte Folded Reload
	jne	.LBB6_23
	jmp	.LBB6_24
.LBB6_16:
	movq	%rbp, %rdx
	callq	memcpy
	testq	%r15, %r15
	jne	.LBB6_19
.LBB6_18:
	movq	(%r14), %rbp
	cmpq	16(%rsp), %rbp          # 8-byte Folded Reload
	je	.LBB6_24
.LBB6_23:
	movq	%rbp, %rdi
	callq	_ZdlPv
.LBB6_24:
	movq	%r12, (%r14)
	movq	%r13, 16(%r14)
	addq	$24, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB6_26:
	.cfi_def_cfa_offset 80
	callq	_ZSt17__throw_bad_allocv
.Lfunc_end6:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, .Lfunc_end6-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_cohen_chess.cpp
	.type	_GLOBAL__sub_I_cohen_chess.cpp,@function
_GLOBAL__sub_I_cohen_chess.cpp:         # @_GLOBAL__sub_I_cohen_chess.cpp
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	movq	$_ZN11cohen_chessL20kFenStartingPositionB5cxx11E+16, _ZN11cohen_chessL20kFenStartingPositionB5cxx11E(%rip)
	movl	$57, %edi
	callq	_Znwm
	movq	%rax, _ZN11cohen_chessL20kFenStartingPositionB5cxx11E(%rip)
	movq	$56, _ZN11cohen_chessL20kFenStartingPositionB5cxx11E+16(%rip)
	movups	.L.str(%rip), %xmm0
	movups	%xmm0, (%rax)
	movups	.L.str+16(%rip), %xmm0
	movups	%xmm0, 16(%rax)
	movups	.L.str+32(%rip), %xmm0
	movups	%xmm0, 32(%rax)
	movabsq	$3539882221867397483, %rcx # imm = 0x312030202D20716B
	movq	%rcx, 48(%rax)
	movq	$56, _ZN11cohen_chessL20kFenStartingPositionB5cxx11E+8(%rip)
	movb	$0, 56(%rax)
	movl	$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev, %edi
	movl	$_ZN11cohen_chessL20kFenStartingPositionB5cxx11E, %esi
	movl	$__dso_handle, %edx
	popq	%rax
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit            # TAILCALL
.Lfunc_end7:
	.size	_GLOBAL__sub_I_cohen_chess.cpp, .Lfunc_end7-_GLOBAL__sub_I_cohen_chess.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZN11cohen_chess8bitboard9kRayTableILa0EEE,@object # @_ZN11cohen_chess8bitboard9kRayTableILa0EEE
	.section	.rodata,"a",@progbits
	.globl	_ZN11cohen_chess8bitboard9kRayTableILa0EEE
	.p2align	3
_ZN11cohen_chess8bitboard9kRayTableILa0EEE:
	.zero	512
	.size	_ZN11cohen_chess8bitboard9kRayTableILa0EEE, 512

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	_ZN11cohen_chessL20kFenStartingPositionB5cxx11E,@object # @_ZN11cohen_chessL20kFenStartingPositionB5cxx11E
	.local	_ZN11cohen_chessL20kFenStartingPositionB5cxx11E
	.comm	_ZN11cohen_chessL20kFenStartingPositionB5cxx11E,32,8
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
	.size	.L.str, 57

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"vector::_M_realloc_insert"
	.size	.L.str.2, 26

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"basic_string::_M_construct null not valid"
	.size	.L.str.3, 42

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"basic_string::_M_create"
	.size	.L.str.4, 24

	.type	_ZN11cohen_chess8bitboard9kRayTableILa8EEE,@object # @_ZN11cohen_chess8bitboard9kRayTableILa8EEE
	.section	.rodata._ZN11cohen_chess8bitboard9kRayTableILa8EEE,"aG",@progbits,_ZN11cohen_chess8bitboard9kRayTableILa8EEE,comdat
	.weak	_ZN11cohen_chess8bitboard9kRayTableILa8EEE
	.p2align	3
_ZN11cohen_chess8bitboard9kRayTableILa8EEE:
	.quad	72340172838076672       # 0x101010101010100
	.quad	144680345676153344      # 0x202020202020200
	.quad	289360691352306688      # 0x404040404040400
	.quad	578721382704613376      # 0x808080808080800
	.quad	1157442765409226752     # 0x1010101010101000
	.quad	2314885530818453504     # 0x2020202020202000
	.quad	4629771061636907008     # 0x4040404040404000
	.quad	-9187201950435737600    # 0x8080808080808000
	.quad	72340172838076416       # 0x101010101010000
	.quad	144680345676152832      # 0x202020202020000
	.quad	289360691352305664      # 0x404040404040000
	.quad	578721382704611328      # 0x808080808080000
	.quad	1157442765409222656     # 0x1010101010100000
	.quad	2314885530818445312     # 0x2020202020200000
	.quad	4629771061636890624     # 0x4040404040400000
	.quad	-9187201950435770368    # 0x8080808080800000
	.quad	72340172838010880       # 0x101010101000000
	.quad	144680345676021760      # 0x202020202000000
	.quad	289360691352043520      # 0x404040404000000
	.quad	578721382704087040      # 0x808080808000000
	.quad	1157442765408174080     # 0x1010101010000000
	.quad	2314885530816348160     # 0x2020202020000000
	.quad	4629771061632696320     # 0x4040404040000000
	.quad	-9187201950444158976    # 0x8080808080000000
	.quad	72340172821233664       # 0x101010100000000
	.quad	144680345642467328      # 0x202020200000000
	.quad	289360691284934656      # 0x404040400000000
	.quad	578721382569869312      # 0x808080800000000
	.quad	1157442765139738624     # 0x1010101000000000
	.quad	2314885530279477248     # 0x2020202000000000
	.quad	4629771060558954496     # 0x4040404000000000
	.quad	-9187201952591642624    # 0x8080808000000000
	.quad	72340168526266368       # 0x101010000000000
	.quad	144680337052532736      # 0x202020000000000
	.quad	289360674105065472      # 0x404040000000000
	.quad	578721348210130944      # 0x808080000000000
	.quad	1157442696420261888     # 0x1010100000000000
	.quad	2314885392840523776     # 0x2020200000000000
	.quad	4629770785681047552     # 0x4040400000000000
	.quad	-9187202502347456512    # 0x8080800000000000
	.quad	72339069014638592       # 0x101000000000000
	.quad	144678138029277184      # 0x202000000000000
	.quad	289356276058554368      # 0x404000000000000
	.quad	578712552117108736      # 0x808000000000000
	.quad	1157425104234217472     # 0x1010000000000000
	.quad	2314850208468434944     # 0x2020000000000000
	.quad	4629700416936869888     # 0x4040000000000000
	.quad	-9187343239835811840    # 0x8080000000000000
	.quad	72057594037927936       # 0x100000000000000
	.quad	144115188075855872      # 0x200000000000000
	.quad	288230376151711744      # 0x400000000000000
	.quad	576460752303423488      # 0x800000000000000
	.quad	1152921504606846976     # 0x1000000000000000
	.quad	2305843009213693952     # 0x2000000000000000
	.quad	4611686018427387904     # 0x4000000000000000
	.quad	-9223372036854775808    # 0x8000000000000000
	.zero	64
	.size	_ZN11cohen_chess8bitboard9kRayTableILa8EEE, 512

	.type	_ZN11cohen_chess10AsciiBoard12kInitialDataE,@object # @_ZN11cohen_chess10AsciiBoard12kInitialDataE
	.section	.rodata._ZN11cohen_chess10AsciiBoard12kInitialDataE,"aG",@progbits,_ZN11cohen_chess10AsciiBoard12kInitialDataE,comdat
	.weak	_ZN11cohen_chess10AsciiBoard12kInitialDataE
_ZN11cohen_chess10AsciiBoard12kInitialDataE:
	.ascii	". . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n"
	.size	_ZN11cohen_chess10AsciiBoard12kInitialDataE, 128

	.type	.L.str.6,@object        # @.str.6
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.6:
	.asciz	"vector::_M_range_check: __n (which is %zu) >= this->size() (which is %zu)"
	.size	.L.str.6, 74

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_cohen_chess.cpp
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_cohen_chess.cpp
	.addrsig_sym _Unwind_Resume
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZN11cohen_chessL20kFenStartingPositionB5cxx11E
	.addrsig_sym _ZSt4cout
