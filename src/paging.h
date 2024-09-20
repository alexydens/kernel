/* Include guard */
#ifndef _PAGING_H
#define _PAGING_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include "symbols.h"

/* Consts */
/* Page directory entry flags */
#define _PDE_FLAGS_PRESENT   (1 << 0)
#define _PDE_FLAGS_RW        (1 << 1)
#define _PDE_FLAGS_USER      (1 << 2)
#define _PDE_FLAGS_PWT       (1 << 3)
#define _PDE_FLAGS_PCD       (1 << 4)
#define _PDE_FLAGS_ACCESSED  (1 << 5)
#define _PDE_FLAGS_DIRTY     (1 << 6)
#define _PDE_FLAGS_SIZE      (1 << 7)
/* Page table entry flags */
#define _PTE_FLAGS_PRESENT   (1 << 0)
#define _PTE_FLAGS_RW        (1 << 1)
#define _PTE_FLAGS_USER      (1 << 2)
#define _PTE_FLAGS_PWT       (1 << 3)
#define _PTE_FLAGS_PCD       (1 << 4)
#define _PTE_FLAGS_ACCESSED  (1 << 5)
#define _PTE_FLAGS_DIRTY     (1 << 6)
#define _PTE_FLAGS_SIZE      (1 << 7)

/* Page directory entry */
typedef struct {
  uint32_t base:  20;
  uint32_t flags: 12;
} __attribute__((packed)) _pde_entry_t;

/* Page table entry */
typedef struct {
  uint32_t base:  20;
  uint32_t flags: 12;
} __attribute__((packed)) _pte_entry_t;

/* Flush a page that has recently been remapped */
extern void _flush_page(uint32_t address);

/* Create a page directory entry */
static inline _pde_entry_t _pde_entry(uint32_t base, uint32_t flags) {
  _pde_entry_t entry;
  entry.base = base;
  entry.flags = flags;
  return entry;
}
/* Create a page table entry */
static inline _pte_entry_t _pte_entry(uint32_t base, uint32_t flags) {
  _pte_entry_t entry;
  entry.base = base;
  entry.flags = flags;
  return entry;
}

#endif /* _PAGING_H */
