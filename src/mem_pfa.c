/* Implements mem/pfa.h */
#include <mem/pfa.h>

/* Consts */
/* Size of a page in bytes */
#define PAGE_SIZE             0x1000

/* Globals */
/* PFA bitmap: 0 = free page, 1 = used page */
static u8 bitmap[0x100000000/(PAGE_SIZE*8)];

/* Initialize the page frame allocator */
bool pfa_init(multiboot_info_t *mb_info) {
  /* Set the bitmap to all used */
  memset(bitmap, 0xff, sizeof(bitmap));

  /* Set all available pages to free */
  serial_printf("MEMORY MAP:\r\n");
  for (
      u32 i = 0;
      i < mb_info->mmap_length/sizeof(multiboot_memory_map_t);
      i++
  ) {
    multiboot_memory_map_t *entry =
        (multiboot_memory_map_t *)(
            mb_info->mmap_addr + 0xc0000000 + i*sizeof(multiboot_memory_map_t)
        );
    serial_printf(
        "- addr: 0x%08X%08X, length: 0x%08X%08X, type: %s\r\n",
        entry->addr_high, entry->addr_low,
        entry->len_high, entry->len_low,
        entry->type == MULTIBOOT_MEMORY_AVAILABLE ? "available" : "reserved"
    );
    if (
        entry->type == MULTIBOOT_MEMORY_AVAILABLE
        && ((u64)entry->addr_low + entry->len_low < 0x100000000)
        && (entry->addr_high == 0)
        && (entry->addr_low > 0x10000)
    ) {
      /* Mark this entry as available */
      for (
          u32 addr = entry->addr_low;
          addr < entry->addr_low + entry->len_low;
          addr += PAGE_SIZE
      ) {
        bitmap[addr/(PAGE_SIZE*8)] &= ~(1 << ((addr/PAGE_SIZE)%8));
      }
    }
  }

  return true;
}

/* Get a free page frame */
u32 pfa_get_frame(void) {
  /* Find a free page */
  for (
      u32 i = 0;
      i < 0x100000000/(PAGE_SIZE*8);
      i++
  ) {
    if (bitmap[i] == 0xff) continue;
    for (u32 j = 0; j < 8; j++) {
      if (!(bitmap[i] & (1 << j))) {
        bitmap[i] |= 1 << j;
        return (i*8+j)*PAGE_SIZE;
      }
    }
  }
  return 0;
}
/* Mark a page frame as free */
void pfa_free_frame(u32 frame) {
  bitmap[frame/(PAGE_SIZE*8)] |= 1 << ((frame/PAGE_SIZE)%8);
}
