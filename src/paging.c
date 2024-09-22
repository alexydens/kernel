/* Implements paging.h */
#include "paging.h"

/* Consts */
#define PTE_MEM_START       (0xc0400000)
#define PTE_MEM_SIZE        (0x400000)

/* Globals */
pde_entry_t *page_dir = (pde_entry_t *)_INIT_PD;
pte_entry_t *page_table0 = (pte_entry_t *)_INIT_PT0;
__attribute__((aligned(0x1000)))
pte_entry_t page_table1[1024];

/* Flush a page that has recently been remapped */
void flush_page(uint32_t address) {
  __asm__ __volatile__ ("invlpg (%0)" : : "r" (address));
}

/* Initializes paging */
void paging_init(void) {
  /*
   * We need some space for the page tables. To find space for this, I'm adding
   * a page table to remap 0x400000 bytes of memory to the higher half for our
   * use:
   * 0x00400000-0x007fffff -> 0xc0400000-0xc07fffff
   */
  /* Create the requisite page table */
  for (uint16_t i = 0; i < 1024; i++) {
    page_table1[i] = pte_entry(
        0x400000 + i * 0x1000,
        PTE_FLAGS_PRESENT
        | PTE_FLAGS_RW
    );
  }
  /* Create the page directory entry */
  page_dir[0x301] = pde_entry(
      (uint32_t)page_table1 - 0xc0000000,
      PDE_FLAGS_PRESENT
      | PDE_FLAGS_RW
  );

  /* Fill the cleared out area with non-present readwrite pages */
  /* There are 1022 spaces left in the PD */
  for (uint16_t i = 0; i < 1024; i++) {
    ((uint32_t*)PTE_MEM_START)[i] = 0x00000002;
  }
  /*
   * NOTE: I was completely expecting a page fault and 30mins of debugging asm
   * after that code, but it seems like it actually worked first try :)
   */

  /* Put the page tables into the page directory */
  for (uint16_t i = 0; i < 1024; i++) {
    /* I'm already using these, I can't remap them. */
    if (i == 0x301) continue;
    if (i == 0x300) continue;
    page_dir[i] = pde_entry(
        PTE_MEM_START + i * 0x1000,
        PDE_FLAGS_PRESENT
        | PDE_FLAGS_RW
    );
  }
}

/* Map a page frame */
void map_page_frame(
    uint32_t physical_addr,
    uint32_t virtual_addr,
    uint8_t flags
) {
  uint16_t pde_index = virtual_addr >> 22;
  uint16_t pte_index = (virtual_addr >> 12) & 0x3ff;

  if (pde_index == 0x300) page_table0[pte_index] = pte_entry(
      physical_addr,
      flags
  );
  else if (pde_index == 0x301) page_table1[pte_index] = pte_entry(
      physical_addr,
      flags
  );
  else ((pte_entry_t*)(PTE_MEM_START))[pte_index + pde_index * 1024] = pte_entry(
      physical_addr,
      flags
  );
}
