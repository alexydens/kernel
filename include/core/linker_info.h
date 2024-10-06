/* Include guard */
#ifndef _CORE_LINKER_INFO_H
#define _CORE_LINKER_INFO_H

/* Includes */
#include <core/types.h>

/* INFORMATION FROM LINKER */
/* NOTE: This variable has no value, its address is the relevant detail */
extern u32 _start_kernel;
/* NOTE: This variable has no value, its address is the relevant detail */
extern u32 _end_kernel;
/* Size of the kernel */
#define KERNEL_SIZE (&_end_kernel - &_start_kernel)
/* The initial page table */
extern u32 _init_PT0[1024];
/* The initial page directory */
extern u32 _init_PD[1024];

#endif /* _CORE_LINKER_INFO_H */
