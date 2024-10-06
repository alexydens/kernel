/* Include guard */
#ifndef _SYS_GDT_H
#define _SYS_GDT_H

/* Includes */
#include <core/types.h>

/* Macros */
#define GDT_SEGMENT_SELECTOR(segment, dpl) ((segment) << 3 | (dpl))

/* Consts */
/* The dimensions of the segments */
/* Physical address of start of kernel code segment */
#define PHYS_START_KERNEL_CODE_SEG  (0x00000000)
/* Size of kernel code segment, in pages */
#define KERNEL_CODE_SEG_SIZE        (0xfffff)
/* Physical address of start of kernel data segment */
#define PHYS_START_KERNEL_DATA_SEG  (0x00000000)
/* Size of kernel data segment, in pages */
#define KERNEL_DATA_SEG_SIZE        (0xfffff)
/* Physical address of start of user code segment */
#define PHYS_START_USER_CODE_SEG    (0x00000000)
/* Size of user code segment, in pages */
#define USER_CODE_SEG_SIZE          (0xfffff)
/* Physical address of start of user data segment */
#define PHYS_START_USER_DATA_SEG    (0x00000000)
/* Size of user data segment, in pages */
#define USER_DATA_SEG_SIZE          (0xfffff)
/* Selector of kernel code segment */
#define GDT_SELECTOR_KERNELCODE     GDT_SEGMENT_SELECTOR(1, 0)
/* Selector of kernel data segment */
#define GDT_SELECTOR_KERNELDATA     GDT_SEGMENT_SELECTOR(2, 0)
/* Selector of user code segment */
#define GDT_SELECTOR_USERCODE       GDT_SEGMENT_SELECTOR(3, 3)
/* Selector of user data segment */
#define GDT_SELECTOR_USERDATA       GDT_SEGMENT_SELECTOR(4, 3)

/* Initialize GDT (return false on error) */
extern bool gdt_init(void);
/* Has the GDT been initialized? */
extern bool gdt_initialized(void);

#endif /* _SYS_GDT_H */
