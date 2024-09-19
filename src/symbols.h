/* Include guard */
#ifndef _SYMBOLS_H
#define _SYMBOLS_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Physical start address of kernel */
#define _PHYS_START_KERNEL          (&_phys_start_kernel)
extern uint32_t _phys_start_kernel;
/* Physical end address of kernel */
#define _PHYS_END_KERNEL            (&_phys_end_kernel)
extern uint32_t _phys_end_kernel;
/* Virtual start address of kernel */
#define _START_KERNEL               (&_start_kernel)
extern uint32_t _start_kernel;
/* Virtual end address of kernel */
#define _END_KERNEL                 (&_end_kernel)
extern uint32_t _end_kernel;

/* Address of initial page directory */
#define _INIT_PD                    (&_init_PD)
extern uint32_t _init_PD;
/* Address of initial page table */
#define _INIT_PT                    (&_init_PT)
extern uint32_t _init_PT;

#endif /* _SYMBOLS_H */
