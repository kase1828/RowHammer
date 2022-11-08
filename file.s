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
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	mov	w0, #1
	bl	_sleep
	ldur	x8, [x29, #-8]
	str	x8, [sp, #16]
	str	wzr, [sp, #12]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #12]
	subs	w8, w8, #17
	b.ge	LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp, #16]
	ldr	x8, [x8]
	subs	x8, x8, #32
	ldrsw	x9, [sp, #12]
	ldr	w8, [x8, x9, lsl #2]
	ldr	x9, [sp, #16]
	add	x9, x9, #16
	ldrsw	x10, [sp, #12]
	str	w8, [x9, x10, lsl #2]
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	LBB1_1
LBB1_4:
	b	LBB1_5
LBB1_5:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB1_6 Depth 2
	str	wzr, [sp, #8]
	b	LBB1_6
LBB1_6:                                 ;   Parent Loop BB1_5 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #8]
	subs	w8, w8, #17
	b.ge	LBB1_11
	b	LBB1_7
LBB1_7:                                 ;   in Loop: Header=BB1_6 Depth=2
	ldr	x8, [sp, #16]
	ldr	x8, [x8]
	subs	x8, x8, #32
	ldrsw	x9, [sp, #8]
	ldr	w8, [x8, x9, lsl #2]
	ldr	x9, [sp, #16]
	add	x9, x9, #16
	ldrsw	x10, [sp, #8]
	ldr	w9, [x9, x10, lsl #2]
	subs	w8, w8, w9
	b.eq	LBB1_9
	b	LBB1_8
LBB1_8:
	mov	x0, #0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
LBB1_9:                                 ;   in Loop: Header=BB1_6 Depth=2
	b	LBB1_10
LBB1_10:                                ;   in Loop: Header=BB1_6 Depth=2
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
	b	LBB1_6
LBB1_11:                                ;   in Loop: Header=BB1_5 Depth=1
	b	LBB1_5
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
