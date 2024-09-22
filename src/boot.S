/* Multiboot consts */
.set ALIGN,   1<<0                /* align loaded modules */
.set MEMINFO, 1<<1                /* provide memory map */
.set VIDINFO, 1<<2                /* provide video info */
.set FLAGS,   ALIGN | MEMINFO | VIDINFO /* multiboot 'flags' */
.set MAGIC,   0x1BADB002					/* magic num so bootloader finds header */
.set CHECKSUM, -(MAGIC + FLAGS)		/* checksum prooves this is multiboot */

/*
Create a multiboot header.
The header marks the program as a kernel.
The bootloader finds this in the first *KiB of kernel (align 32-bit bounds).
*/
.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0, 0, 0, 0, 0
.long 1
.long 0, 0, 0
/*.long 0
.long 1920, 1080, 0*/

/*
Reserve stack space.
16384 bytes, growing downwards.
The stack is 16-byte aligned.
*/
.section .init_stack, "aw", @nobits
.globl stack_top
.align 16
_stack_bottom:
.skip 16384
_stack_top:

/* Reserve space for the page directory and the first page table */
.section .bss, "aw", @nobits
.global _init_PD
.global _init_PT0
.align 4096
_init_PD:
.skip 4096
_init_PT0:
.skip 4096

/*
The entry point is _start. This is linked in from the bootloader
*/
.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:
  /* Keep track of the physical address of the first page table */
  movl $(_init_PT0 - 0xc0000000), %edi
  /* ESI will store the physical address of the page being allocated */
  movl $0x0, %esi
  /* The ECX stores loop count. In this case, we loop one time for each PF */
  /* (1023 times - in hex for consistency) */
  movl $0x3ff, %ecx

1:
  /* If the pointer is less than the start of kernel, go to 1: */
  cmpl $_phys_start_kernel, %esi
  jl 2f
  /* If the pointer is greater than or equal to the end, go to 2: */
  cmpl $_phys_end_kernel, %esi
  jge 3f

  /* Otherwise, add page table entry of 'present, writable' */
  movl %esi, %edx
  orl $0x3, %edx
  movl %edx, (%edi)

2:
  /* We are before the kernel. Don't add this entry */
  /* Skip over the next 4096 bytes */
  addl $0x1000, %esi
  /* Skip over the next PT entry */
  addl $0x4, %edi
  /* Loop back */
  loop 1b

3:
  /* We are after the kernel. It's go time! */
  /* Add the VGA memory to the last page in the first table */
  movl $(0x000b8000 | 0x3), _init_PT0 - 0xc0000000 + 0x3ff * 0x4

  /* 
  We are going to need the a page directory entry to boot into, but then
  we want a different one pointing to the higher half. We create 2 now, and 
  remove the first one later.
  */
  movl $(_init_PT0 - 0xc0000000 + 0x3), _init_PD - 0xc0000000
  movl $(_init_PT0 - 0xc0000000 + 0x3), _init_PD - 0xc0000000 + 0xc00

  /* Now, we are ready to load the directory */
  /* Load the address of the page directory into CR3 */
  movl $(_init_PD - 0xc0000000), %ecx
  movl %ecx, %cr3
  /* Enable paging (and write protect) */
  movl %cr0, %ecx
  orl $0x80010001, %ecx
  movl %ecx, %cr0

  /* Jump into the higher half, label 3 */
  lea 4f, %ecx
  jmp *%ecx

.section .text
4:
  /* Unmap the first page table */
  movl $0x0, _init_PD

  /* Reload the page directory */
  movl %cr3, %ecx
  movl %ecx, %cr3

  /* Put the stack registers in the right places */
  movl $_stack_top, %esp

  /* Call kernel - linked in C function */
  call kernel_main

  /* If kernel returns, hang */
  cli
1:
  hlt
  jmp 1b
