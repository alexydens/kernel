/* Include guard */
#ifndef _MEM_VMM_H
#define _MEM_VMM_H

/* The virtual memory manager */

/* Includes */
#include <core/types.h>
#include <io/serial.h>
#include <mem/page_frame_alloc.h>

/* Initialize the virtual memory manager (return false on error) */
extern bool vmm_init(void);
/* Has the virtual memory manager been initialized? */
extern bool vmm_initialized(void);

/* Set the current page directory to pd (& load into cr3) */
extern void vmm_switch_page_directory(void *pd);
/* Create a new page directory */
extern void *vmm_create_page_directory(void);
/* Destroy a page directory */
extern void vmm_destroy_page_directory(void *pd);
/* Map a page frame */
extern void vmm_map_page(void *virt_addr);

#endif /* _MEM_VMM_H */
