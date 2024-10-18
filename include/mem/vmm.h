/* Include guard */
#ifndef MEM_VMM_H
#define MEM_VMM_H

/* Includes */
#include <core/base.h>
#include <io/serial.h>
#include <mem/pfa.h>

/* Consts */
/* Page types */
#define VMM_PAGE_TYPE_KERNEL  0 /* A kernel page */
#define VMM_PAGE_TYPE_USER    1 /* A user page */

/* Initialize the virtual memory manager */
extern bool vmm_init(void);

/* Create a new page directory */
extern u32 vmm_create_page_directory(void);
/* Switch to a page directory */
extern void vmm_switch_page_directory(u32 pd);
/* Delete a page directory */
extern void vmm_delete_page_directory(u32 pd);

/* Map a page of virtual memory */
extern void vmm_map_page(u32 virtual_addr, u8 type);
/* Unmap a page of virtual memory */
extern void vmm_unmap_page(u32 virtual_addr);

#endif /* MEM_VMM_H */
