/* Include guard */
#ifndef _PAGING_H
#define _PAGING_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include "symbols.h"

/* Consts */
/* Page directory entry flags */
#define PDE_FLAGS_PRESENT       (1 << 0)
#define PDE_FLAGS_RW            (1 << 1)
#define PDE_FLAGS_USER          (1 << 2)
#define PDE_FLAGS_PWT           (1 << 3)
#define PDE_FLAGS_PCD           (1 << 4)
#define PDE_FLAGS_ACCESSED      (1 << 5)
#define PDE_FLAGS_DIRTY         (1 << 6)
#define PDE_FLAGS_SIZE          (1 << 7)
/* Page table entry flags */
#define PTE_FLAGS_PRESENT       (1 << 0)
#define PTE_FLAGS_RW            (1 << 1)
#define PTE_FLAGS_USER          (1 << 2)
#define PTE_FLAGS_PWT           (1 << 3)
#define PTE_FLAGS_PCD           (1 << 4)
#define PTE_FLAGS_ACCESSED      (1 << 5)
#define PTE_FLAGS_DIRTY         (1 << 6)
#define PTE_FLAGS_SIZE          (1 << 7)

/* Macros */
/* Get a flag's status from a PD or PT entry (pass in flag and ptr to entry */
#define PAGING_CHECK_FLAG(f, p) (((*p) & f) == 0 ? 0 : 1)

/* Page directory entry */
typedef uint32_t pde_entry_t;
/* Page table entry */
typedef uint32_t pte_entry_t;

/* Create a page directory entry */
static inline pde_entry_t pde_entry(uint32_t base, uint32_t flags) {
  return (uint32_t)base | flags;
}
/* Create a page table entry */
static inline pte_entry_t pte_entry(uint32_t base, uint32_t flags) {
  return (uint32_t)base | flags;
}

/* Flush a page that has recently been remapped */
extern void flush_page(uint32_t address);
/* Reloads page directory */
extern void reload_pd(void);
/* Initializes paging */
extern void paging_init(void);

#endif /* _PAGING_H */
