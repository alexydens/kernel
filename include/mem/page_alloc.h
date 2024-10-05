/* Include guard */
#ifndef _MEM_PAGE_ALLOC_H
#define _MEM_PAGE_ALLOC_H

/* Includes */
#include <core/types.h>
#include <core/utils.h>
#include <sys/paging.h>
#include <mem/map.h>
#include <io/vga_term.h>

/* Macros */
#define PAGE_TYPE_KERNEL_HEAP   0
#define PAGE_TYPE_USER_HEAP     1

/* Initialilze page allocator */
extern void page_alloc_init(void);
/* Get num_pages free pages */
extern void *get_free_pages(u32 type, size_t num_pages);
/* Mark num_pages starting from addr as free */
extern void free_pages(u32 type, void *addr, size_t num_pages);
/* Print 25 rows of the bitmap to the vga terminal */
extern void print_bitmap(u32 type);

#endif /* _MEM_PAGE_ALLOC_H */
