/* Multiboot consts */
.set MAGIC,   0x1BADB002					/* magic num so bootloader finds header */
.set CHECKSUM, -(MAGIC + FLAGS)		/* checksum prooves this is multiboot */
.set ALIGN,   1<<0                /* align loaded modules on page boundaries */
.set MEMINFO, 1<<1                /* provide memory map */
.set VIDINFO, 1<<2                /* provide video information */
/* multiboot 'flags' */
.set FLAGS,   ALIGN | MEMINFO | VIDINFO

/*
Create a multiboot header.
The header marks the program as a kernel.
The bootloader finds this in the first *KiB of kernel (align 32-bit bounds).
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0, 0, 0, 0, 0
.long 1         /* video mode: text */
.long 0, 0, 0

/*
Reserve stack space.
16384 bytes, growing downwards.
The stack is 16-byte aligned.
*/
.section .bss
.globl stack_top
.align 16
stack_bottom:
.skip 16384
stack_top:

/*
The entry point is _start. This is linked in from the bootloader.
*/
.section .text
.global _start
.type _start, @function
_start:
  /*
  Mode: 32-bit protected.
  BIOS interrupts dissabled, no paging.
  */

  /* Set up the stack. */
  movl $stack_top, %esp

  /* Call kernel - linked in C function */
  call kernel_main

  /* Hang if kernel returns. */
  cli
1: hlt
  jmp 1b
.size _start, . - _start
