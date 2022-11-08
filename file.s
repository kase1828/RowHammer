	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	_rowhammer                      ; -- Begin function rowhammer
	.p2align	2
_rowhammer:                             ; @rowhammer
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	str	x8, [sp]
	ldr	x9, [sp]
	; InlineAsm Start
	mov	x9, x8	;
	; InlineAsm End
	str	x8, [x9]
	ldr	x9, [sp]
	; InlineAsm Start
	mov	x10, x8	;
	; InlineAsm End
	str	x8, [x9, #8]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	; InlineAsm Start
	str	x0, [x9]
	str	x0, [x10]
	dc	cvac, x9
	dc	cvac, x10
	; InlineAsm End
	b	LBB0_1
	.cfi_endproc
                                        ; -- End function
	.globl	_check                          ; -- Begin function check
	.p2align	2
_check:                                 ; @check
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #8]
	mov	w0, #1
	bl	_sleep
	ldr	x8, [sp, #8]
	str	x8, [sp]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-32]
	ldr	x9, [sp]
	str	w8, [x9, #20]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-28]
	ldr	x9, [sp]
	str	w8, [x9, #24]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-24]
	ldr	x9, [sp]
	str	w8, [x9, #28]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-20]
	ldr	x9, [sp]
	str	w8, [x9, #32]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-16]
	ldr	x9, [sp]
	str	w8, [x9, #36]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-12]
	ldr	x9, [sp]
	str	w8, [x9, #40]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-8]
	ldr	x9, [sp]
	str	w8, [x9, #44]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-4]
	ldr	x9, [sp]
	str	w8, [x9, #48]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8]
	ldr	x9, [sp]
	str	w8, [x9, #16]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #4]
	ldr	x9, [sp]
	str	w8, [x9, #52]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #8]
	ldr	x9, [sp]
	str	w8, [x9, #56]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #12]
	ldr	x9, [sp]
	str	w8, [x9, #60]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #16]
	ldr	x9, [sp]
	str	w8, [x9, #64]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #20]
	ldr	x9, [sp]
	str	w8, [x9, #68]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #24]
	ldr	x9, [sp]
	str	w8, [x9, #72]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #28]
	ldr	x9, [sp]
	str	w8, [x9, #76]
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #32]
	ldr	x9, [sp]
	str	w8, [x9, #80]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-32]
	ldr	x9, [sp]
	ldr	w9, [x9, #20]
	subs	w8, w8, w9
	b.eq	LBB1_3
	b	LBB1_2
LBB1_2:
	b	LBB1_36
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-28]
	ldr	x9, [sp]
	ldr	w9, [x9, #24]
	subs	w8, w8, w9
	b.eq	LBB1_5
	b	LBB1_4
LBB1_4:
	b	LBB1_36
LBB1_5:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-24]
	ldr	x9, [sp]
	ldr	w9, [x9, #28]
	subs	w8, w8, w9
	b.eq	LBB1_7
	b	LBB1_6
LBB1_6:
	b	LBB1_36
LBB1_7:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-20]
	ldr	x9, [sp]
	ldr	w9, [x9, #32]
	subs	w8, w8, w9
	b.eq	LBB1_9
	b	LBB1_8
LBB1_8:
	b	LBB1_36
LBB1_9:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-16]
	ldr	x9, [sp]
	ldr	w9, [x9, #36]
	subs	w8, w8, w9
	b.eq	LBB1_11
	b	LBB1_10
LBB1_10:
	b	LBB1_36
LBB1_11:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-12]
	ldr	x9, [sp]
	ldr	w9, [x9, #40]
	subs	w8, w8, w9
	b.eq	LBB1_13
	b	LBB1_12
LBB1_12:
	b	LBB1_36
LBB1_13:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-8]
	ldr	x9, [sp]
	ldr	w9, [x9, #44]
	subs	w8, w8, w9
	b.eq	LBB1_15
	b	LBB1_14
LBB1_14:
	b	LBB1_36
LBB1_15:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldur	w8, [x8, #-4]
	ldr	x9, [sp]
	ldr	w9, [x9, #48]
	subs	w8, w8, w9
	b.eq	LBB1_17
	b	LBB1_16
LBB1_16:
	b	LBB1_36
LBB1_17:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8]
	ldr	x9, [sp]
	ldr	w9, [x9, #16]
	subs	w8, w8, w9
	b.eq	LBB1_19
	b	LBB1_18
LBB1_18:
	b	LBB1_36
LBB1_19:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #4]
	ldr	x9, [sp]
	ldr	w9, [x9, #52]
	subs	w8, w8, w9
	b.eq	LBB1_21
	b	LBB1_20
LBB1_20:
	b	LBB1_36
LBB1_21:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #8]
	ldr	x9, [sp]
	ldr	w9, [x9, #56]
	subs	w8, w8, w9
	b.eq	LBB1_23
	b	LBB1_22
LBB1_22:
	b	LBB1_36
LBB1_23:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #12]
	ldr	x9, [sp]
	ldr	w9, [x9, #60]
	subs	w8, w8, w9
	b.eq	LBB1_25
	b	LBB1_24
LBB1_24:
	b	LBB1_36
LBB1_25:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #16]
	ldr	x9, [sp]
	ldr	w9, [x9, #64]
	subs	w8, w8, w9
	b.eq	LBB1_27
	b	LBB1_26
LBB1_26:
	b	LBB1_36
LBB1_27:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #20]
	ldr	x9, [sp]
	ldr	w9, [x9, #68]
	subs	w8, w8, w9
	b.eq	LBB1_29
	b	LBB1_28
LBB1_28:
	b	LBB1_36
LBB1_29:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #24]
	ldr	x9, [sp]
	ldr	w9, [x9, #72]
	subs	w8, w8, w9
	b.eq	LBB1_31
	b	LBB1_30
LBB1_30:
	b	LBB1_36
LBB1_31:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #28]
	ldr	x9, [sp]
	ldr	w9, [x9, #76]
	subs	w8, w8, w9
	b.eq	LBB1_33
	b	LBB1_32
LBB1_32:
	b	LBB1_36
LBB1_33:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp]
	ldr	x8, [x8]
	ldr	w8, [x8, #32]
	ldr	x9, [sp]
	ldr	w9, [x9, #80]
	subs	w8, w8, w9
	b.eq	LBB1_35
	b	LBB1_34
LBB1_34:
	b	LBB1_36
LBB1_35:                                ;   in Loop: Header=BB1_1 Depth=1
	b	LBB1_1
LBB1_36:
	mov	x0, #0
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0
	str	w8, [sp, #36]                   ; 4-byte Folded Spill
	stur	wzr, [x29, #-4]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	sub	x8, x29, #8
	str	x8, [sp, #8]                    ; 8-byte Folded Spill
	mov	w8, #5
	stur	w8, [x29, #-8]
	sub	x8, x29, #12
	str	x8, [sp, #16]                   ; 8-byte Folded Spill
	mov	w8, #7
	stur	w8, [x29, #-12]
	mov	x0, #88
	bl	_malloc
	ldr	x9, [sp, #8]                    ; 8-byte Folded Reload
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	stur	x0, [x29, #-24]
	ldur	x10, [x29, #-24]
	str	x9, [x10]
	ldur	x9, [x29, #-24]
	str	x8, [x9, #8]
	ldur	x3, [x29, #-24]
	sub	x0, x29, #32
	mov	x1, #0
	str	x1, [sp, #24]                   ; 8-byte Folded Spill
	adrp	x2, _rowhammer@PAGE
	add	x2, x2, _rowhammer@PAGEOFF
	bl	_pthread_create
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	ldr	x1, [sp, #24]                   ; 8-byte Folded Reload
	ldur	x3, [x29, #-24]
	add	x0, sp, #40
	adrp	x2, _check@PAGE
	add	x2, x2, _check@PAGEOFF
	bl	_pthread_create
	ldr	x1, [sp, #24]                   ; 8-byte Folded Reload
	ldr	x0, [sp, #40]
	bl	_pthread_join
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	ldur	x0, [x29, #-32]
	bl	_pthread_cancel
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	ldr	w0, [sp, #36]                   ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"starting...\n"

l_.str.1:                               ; @.str.1
	.asciz	"hammering...\n"

l_.str.2:                               ; @.str.2
	.asciz	"read disturb found\n"

l_.str.3:                               ; @.str.3
	.asciz	"exiting...\n"

.subsections_via_symbols
