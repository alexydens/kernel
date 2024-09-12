/* Include guard */
#if !defined(MEM_PAGING_H)
#define MEM_PAGING_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

/* Initialize and load the PD and PTs */
extern void mem_paging_init(void);

#endif /* MEM_PAGING_H */
