	.arch armv6
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"file.c"
	.text
	.align	2
	.global	rowhammer
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	rowhammer, %function
rowhammer:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
	.syntax divided
@ 18 "file.c" 1
	mov r0, r2;
@ 0 "" 2
	.arm
	.syntax unified
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	.syntax divided
@ 23 "file.c" 1
	mov r1, r2;
@ 0 "" 2
	.arm
	.syntax unified
	ldr	r3, [fp, #-8]
	str	r2, [r3, #4]
.L2:
	.syntax divided
@ 30 "file.c" 1
	STR r2, [%0]	
STR r1, [%1]	
DC CVAC, r0	
DC CVAC, r1	

@ 0 "" 2
	.arm
	.syntax unified
	b	.L2
	.size	rowhammer, .-rowhammer
	.section	.rodata
	.align	2
.LC0:
	.ascii	"searcing...\000"
	.text
	.align	2
	.global	check
	.syntax unified
	.arm
	.fpu vfp
	.type	check, %function
check:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	mov	r0, #1
	bl	sleep
	ldr	r3, [fp, #-24]
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L4
.L5:
	ldr	r3, [fp, #-16]
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #-1073741816
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r1, [r3]
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-8]
	add	r2, r2, #2
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L4:
	ldr	r3, [fp, #-8]
	cmp	r3, #16
	ble	.L5
	ldr	r0, .L12
	bl	puts
.L10:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L6
.L9:
	ldr	r3, [fp, #-16]
	ldr	r2, [r3]
	ldr	r3, [fp, #-12]
	sub	r3, r3, #-1073741816
	lsl	r3, r3, #2
	add	r3, r2, r3
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	ldr	r1, [fp, #-12]
	add	r1, r1, #2
	ldr	r3, [r3, r1, lsl #2]
	cmp	r2, r3
	beq	.L7
	mov	r3, #0
	b	.L11
.L7:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L6:
	ldr	r3, [fp, #-12]
	cmp	r3, #16
	ble	.L9
	b	.L10
.L11:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
.L13:
	.align	2
.L12:
	.word	.LC0
	.size	check, .-check
	.section	.rodata
	.align	2
.LC1:
	.ascii	"starting...\000"
	.align	2
.LC2:
	.ascii	"hammering...\000"
	.align	2
.LC3:
	.ascii	"read disturb found\000"
	.align	2
.LC4:
	.ascii	"exiting...\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	ldr	r0, .L16
	bl	puts
	mov	r3, #5
	str	r3, [fp, #-12]
	mov	r3, #7
	str	r3, [fp, #-16]
	mov	r0, #76
	bl	malloc
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	sub	r2, fp, #12
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	sub	r2, fp, #16
	str	r2, [r3, #4]
	sub	r0, fp, #20
	ldr	r3, [fp, #-8]
	ldr	r2, .L16+4
	mov	r1, #0
	bl	pthread_create
	ldr	r0, .L16+8
	bl	puts
	sub	r0, fp, #24
	ldr	r3, [fp, #-8]
	ldr	r2, .L16+12
	mov	r1, #0
	bl	pthread_create
	ldr	r3, [fp, #-24]
	mov	r1, #0
	mov	r0, r3
	bl	pthread_join
	ldr	r0, .L16+16
	bl	puts
	ldr	r3, [fp, #-20]
	mov	r0, r3
	bl	pthread_cancel
	ldr	r0, .L16+20
	bl	puts
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
.L17:
	.align	2
.L16:
	.word	.LC1
	.word	rowhammer
	.word	.LC2
	.word	check
	.word	.LC3
	.word	.LC4
	.size	main, .-main
	.ident	"GCC: (Raspbian 10.2.1-6+rpi1) 10.2.1 20210110"
	.section	.note.GNU-stack,"",%progbits
