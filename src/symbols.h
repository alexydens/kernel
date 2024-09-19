/* Include guard */
#ifndef _SYMBOLS_H
#define _SYMBOLS_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Physical start address of kernel */
extern uint32_t _phys_start_kernel;
/* Physical end address of kernel */
extern uint32_t _phys_end_kernel;
/* Virtual start address of kernel */
extern uint32_t _start_kernel;
/* Virtual end address of kernel */
extern uint32_t _end_kernel;

#endif /* _SYMBOLS_H */
