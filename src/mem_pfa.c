/* Implements mem/pfa.h */
#include <mem/pfa.h>

/* Consts */
/* Size of a page in bytes */
#define PAGE_SIZE             0x1000
/* Status of a page frame */
#define PAGE_STATUS_FREE      0
#define PAGE_STATUS_USED      1
#define PAGE_STATUS_RESERVED  2

/* Globals */
/*
 * The bitmap for the page frame allocator: 2 bits per page frame, so 4 in
 * each u8.
 */
static u8 bitmap[0x100000000/(PAGE_SIZE*4)];

/* Initialize the page frame allocator */
bool pfa_init(multiboot_info_t *mb_info) {
  /* Zero out the bitmap */
  memset(bitmap, 0, sizeof(bitmap));

  /* Set all reserved pages as reserved */
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
        entry->type != MULTIBOOT_MEMORY_AVAILABLE
        || (u64)entry->addr_low + entry->len_low > 0x100000000
        || entry->addr_high
        || entry->addr_low < 0x10000
    ) {
      /* Mark this entry as reserved */
      for (
          u32 addr = (u32)entry->addr_low;
          addr < (u32)entry->addr_low + entry->len_low;
          addr += PAGE_SIZE
      ) {
        bitmap[addr/(PAGE_SIZE*4)] |=
          PAGE_STATUS_RESERVED << (((addr/PAGE_SIZE)%4)*2);
        //serial_printf(
            //"index: %u offset: %u result: 0x%02x\r\n",
            //addr/(PAGE_SIZE*4),
            //(addr/PAGE_SIZE)%4,
            //bitmap[addr/(PAGE_SIZE*4)]
        //);
      }
    }
  }

  return true;
}

/* Get a free page frame */
u32 pfa_get_frame(void) {
  /* Find a free page */
  for (u32 i = 0; i < 0x100000000/(PAGE_SIZE*4); i++) {
    for (u32 j = 0; j < 4; j++) {
      if ((bitmap[i] & (3 << (j*2))) == 0) {
        bitmap[i] |= PAGE_STATUS_USED << (j*2);
        return (i*4+j)*PAGE_SIZE;
      }
    }
  }
  return 0;
}
/* Mark a page frame as free */
void pfa_free_frame(u32 frame) {
  bitmap[frame/(PAGE_SIZE*4)] &=
    ~(PAGE_STATUS_USED << ((frame%(PAGE_SIZE*4))*2));
}
