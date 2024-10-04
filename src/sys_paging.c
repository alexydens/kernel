/* Implements sys/paging.h */
#include <sys/paging.h>

/* Get u64 from two u32s */
#define GET_U64(high, low) (((u64)high << 32) | (u64)low)

/* Globals */
__attribute__((aligned(0x1000)))
pte_entry_t page_table1[1024];
extern u32 _init_PD;
extern u32 _init_PT0;
pde_entry_t *page_dir;
pte_entry_t *page_table0;
static buf_t _free_memory;

/* Flush a page that has recently been remapped */
void flush_page(u32 address) {
  __asm__ __volatile__ ("invlpg (%0)" : : "r" (address));
}

/* Initializes paging */
void paging_init(multiboot_info_t *mb_info) {
  /* Variables */
  char str[17];

  /* Load the page table and page dir */
  page_dir = (pde_entry_t *)&_init_PD;
  page_table0 = (pte_entry_t *)&_init_PT0;
  /*
   * We need some space for the page tables. To find space for this, I'm adding
   * a page table to remap 0x400000 bytes of memory to the higher half for our
   * use:
   * 0x00400000-0x007fffff -> 0xc0400000-0xc07fffff
   */
  /* Create the requisite page table */
  for (u16 i = 0; i < 1024; i++) {
    page_table1[i] = pte_entry(
        0x400000 + i * 0x1000,
        PTE_FLAGS_PRESENT
        | PTE_FLAGS_RW
    );
  }
  /* Create the page directory entry */
  page_dir[0x301] = pde_entry(
      (u32)page_table1 - 0xc0000000,
      PDE_FLAGS_PRESENT
      | PDE_FLAGS_RW
  );

  /* Fill the cleared out area with non-present readwrite pages */
  for (u32 i = 0; i < 1024 * 1024; i++) {
    ((pte_entry_t *)PTE_MEM_START)[i] = 0x00000002;
  }
  /*
   * NOTE: I was completely expecting a page fault and 30mins of debugging asm
   * after that code, but it seems like it actually worked first try :)
   */

  /* Put the page tables into the page directory */
  for (u16 i = 0; i < 1024; i++) {
    /* I'm already using these, I can't remap them. */
    if (i == 0x301) continue;
    if (i == 0x300) continue;
    page_dir[i] = pde_entry(
        PTE_MEM_START + i * 0x1000 - 0xc0000000,
        PDE_FLAGS_PRESENT
        | PDE_FLAGS_RW
    );
  }

  /* Get memory map */
  /* Flag for valid mmap */
  ASSERT((mb_info->flags >> 6) & 0x1);
  /* Get and log values */
  for (
      u32 i = 0;
      i < mb_info->mmap_length;
      i += sizeof(multiboot_memory_map_t)
  ) {
    multiboot_memory_map_t *mmap =
      (multiboot_memory_map_t *)(mb_info->mmap_addr + i + 0xc0000000);
    str[8] = '\0';
    LOG("Available memory: Start: 0x");
    hex_str_32(mmap->addr_high, str);
    LOG(str);
    hex_str_32(mmap->addr_low, str);
    LOG(str);
    LOG(" Length: 0x");
    hex_str_32(mmap->len_high, str);
    LOG(str);
    hex_str_32(mmap->len_low, str);
    LOG(str);
    LOG(" Available: ");
    LOG(BOOL_STR(mmap->type == MULTIBOOT_MEMORY_AVAILABLE));
    LOG("\r\n");
    if (GET_U64(mmap->len_high, mmap->len_low) > _free_memory.size) {
      _free_memory.ptr = (void *)GET_U64(mmap->addr_high, mmap->addr_low);
      _free_memory.size = GET_U64(mmap->len_high, mmap->len_low);
    }
  }
  str[16] = 0;
  LOG("Address of free memory: 0x");
  hex_str_64((u64)_free_memory.ptr, str);
  LOG(str);
  LOG("\r\n");
  LOG("Size of free memory: 0x");
  hex_str_64(_free_memory.size, str);
  LOG(str);
  LOG("\r\n");
}

/* Get the largest block of free memory available */
buf_t get_free_memory(void) {
  return _free_memory;
}

/* Map a page frame */
void map_page_frame(
    u32 physical_addr,
    u32 virtual_addr,
    u8 flags
) {
  u16 pde_index = (virtual_addr >> 22) & 0x3ff;
  u16 pte_index = (virtual_addr >> 12) & 0x3ff;
  
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
