/* Include guard */
#ifndef MEM_PFA_H
#define MEM_PFA_H

/* Include guard */
#include <core/base.h>
#include <ext/multiboot.h>
#include <io/serial.h>

/* Initialize the page frame allocator */
extern bool pfa_init(multiboot_info_t *mb_info);

/* Get a free page frame */
extern u32 pfa_get_frame(void);
/* Mark a page frame as free */
extern void pfa_free_frame(u32 frame);

#endif /* MEM_PFA_H */
