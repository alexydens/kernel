/* Include guard */
#ifndef SYS_GDT_H
#define SYS_GDT_H

/* Includes */
#include <core/base.h>

/* Consts */
/* The null segment descriptor */
#define GDT_SEGMENT_NULL        ((u16)0x0000)
/* The kernel code segment descriptor */
#define GDT_SEGMENT_KERNELCODE  ((u16)0x0008)
/* The kernel data segment descriptor */
#define GDT_SEGMENT_KERNELDATA  ((u16)0x0010)
/* The user code segment descriptor */
#define GDT_SEGMENT_USERCODE    ((u16)(0x0018|0x0003))
/* The user data segment descriptor */
#define GDT_SEGMENT_USERDATA    ((u16)(0x0020|0x0003))

/* Initialize the GDT */
bool gdt_init(void);

#endif /* SYS_GDT_H */
