/* Include guard */
#ifndef _MEM_MAP_H
#define _MEM_MAP_H

/* Includes */
#include <core/types.h>
#include <sys/paging.h>

/* Consts */
/* Page size */
#define PAGE_SIZE               0x1000

/* Start of physical memory for kernel code and bootloader */
#define PHYS_KERNEL_CODE_START  0x00000000
/* Start of virtual memory for kernel code and bootloader */
#define VIRT_KERNEL_CODE_START  0xc0000000
/* Size of memory for kernel code and bootloader */
#define KERNEL_CODE_SIZE        0x003ff000
/* Size of kernel code itself according to linker */
extern u32 _start_kernel, _end_kernel;
/* Size of kernel code itself according to linker */
#define KERNEL_CODE_SIZE_LINKER (&_end_kernel - &_start_kernel)

/* Start of physical memory for vga buffer */
#define PHYS_VGA_BUFFER_START   0x000b8000
/* Start of virtual memory for vga buffer */
#define VIRT_VGA_BUFFER_START   0xc03ff000
/* Size of memory for vga buffer */
#define VGA_BUFFER_SIZE         0x00001000

/* Start of physical memory for page tables */
#define PHYS_PAGE_TABLES_START  0x00400000
/* Start of virtual memory for page tables */
#define VIRT_PAGE_TABLES_START  0xc0400000
/* Size of memory for page tables */
#define PAGE_TABLES_SIZE        0x00400000

/* Start of virtual memory for kernel heap (no size - it goes to 0xffffffff) */
#define VIRT_KERNEL_HEAP_START  0xc0800000
/* Size of kernel heap */
#define KERNEL_HEAP_SIZE        0x3f7fffff

/* Start of virtual memory for user stack */
#define VIRT_USER_STACK_START   0xa0000000
/* Size of user stack */
#define USER_STACK_SIZE         0x10000000

/* Start of virtual memory for user heap */
#define VIRT_USER_HEAP_START    0x90000000
/* Size of user heap */
#define USER_HEAP_SIZE          0x10000000

/* Start of virtual memory for user code */
#define VIRT_USER_CODE_START    0x00000000
/* Size of user code */
#define USER_CODE_SIZE          0x90000000

#endif /* _MEM_MAP_H */
