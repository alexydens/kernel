/* Include guard */
#ifndef _MEM_PAGE_FRAME_ALLOC_H
#define _MEM_PAGE_FRAME_ALLOC_H

/* Includes */
#include <core/types.h>
#include <core/utils.h>
#include <core/linker_info.h>
#include <ext/multiboot.h>
#include <io/serial.h>

/* Initialize page frame allocator (returns false on error) */
extern bool page_frame_alloc_init(multiboot_info_t *mb_info);
/* Has the page frame allocator been initialized? */
extern bool page_frame_alloc_initialized(void);

/* Get a free page frame */
extern void *get_free_page_frame(void);
/* Mark a page frame as free */
extern void page_frame_free(void *frame);

/* Get the number of free pages */
extern u32 get_free_page_count(void);

#endif /* _MEM_PAGE_FRAME_ALLOC_H */
