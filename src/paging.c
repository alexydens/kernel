/* Implements paging.h */
#include "paging.h"

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
  for (uint16_t i = 0; i < 1024; i++) {
    page_table1[i] = pte_entry(
        i * 0x1000,
        PTE_FLAGS_PRESENT
        | PTE_FLAGS_RW
        | PTE_FLAGS_USER
    );
  }
  page_dir[0x301] = pde_entry(
      (uint32_t)page_table1 - 0xc0000000,
      PDE_FLAGS_PRESENT
      | PDE_FLAGS_RW
      | PTE_FLAGS_USER
  );
  reload_pd();
}
