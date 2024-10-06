/* Implements mem/page_frame_alloc.h */
#include <mem/page_frame_alloc.h>

/* Globals */
static bool initialized = false;
static u32 physical_bitmap[0x100000000/(0x1000*sizeof(u32)*8)];

/* Initialize page frame allocator (returns false on error) */
bool page_frame_alloc_init(multiboot_info_t *mb_info) {
  /* Check multiboot flags for memory map */
  if (!((mb_info->flags >> 6) & 1)) {
    serial_printf("ERROR: No memory map\r\n");
    return false;
  }

  /* Clear bitmap */
  memset(physical_bitmap, 0, sizeof(physical_bitmap));

  /* Loop through mmap */
  for (u32 i = 0; i<mb_info->mmap_length/sizeof(multiboot_memory_map_t); i++) {
    /* Get the next multiboot mmap entry */
    multiboot_memory_map_t *mmap = 
      (multiboot_memory_map_t *)
      (PTR_U32(mb_info->mmap_addr+0xc0000000+i*sizeof(multiboot_memory_map_t)));
    /* Print the information of the memory map, and mark reserved mem as used */
    serial_printf(
        "MMAP ENTRY: addr: 0x%xd%xd, length: 0x%xd%xd, type: ",
        mmap->addr_high, mmap->addr_low,
        mmap->len_high, mmap->len_low,
        mmap->type
    );
    switch (mmap->type) {
      case MULTIBOOT_MEMORY_AVAILABLE:
        /* 
         * If the memory is below 0x00100000, it's probably being used by the
         * bootloader.
         */
        if (mmap->addr_low < 0x00100000
            && mmap->addr_high == 0) {
          serial_printf("Reserved memory\r\n");
          /* Check memory is withing 0x00000000-0xffffffff */
          if (
              mmap->addr_high
              | mmap->len_high
              | ((u64)mmap->addr_low + (u64)mmap->len_low > 0x100000000)
          ) continue;
          /* Mark reserved memory as used */
          for (u32 j = 0; j < mmap->len_low/0x1000; j++) {
            physical_bitmap[
              (mmap->addr_low + j * 0x1000)
              / (sizeof(u32)*8*0x1000)
            ] |= 1 << ((mmap->addr_low + j * 0x1000) % sizeof(u32)*8);
          }
        } else serial_printf("Available memory\r\n");
        break;
      case MULTIBOOT_MEMORY_RESERVED:
        serial_printf("Reserved memory\r\n");
        /* Check memory is withing 0x00000000-0xffffffff */
        if (
            mmap->addr_high
            | mmap->len_high
            | ((u64)mmap->addr_low + (u64)mmap->len_low > 0x100000000)
        ) continue;
        /* Mark reserved memory as used */
        for (u32 j = 0; j < mmap->len_low/0x1000; j++) {
          physical_bitmap[
            (mmap->addr_low + j * 0x1000)
            / (sizeof(u32)*8*0x1000)
          ] |= 1 << ((mmap->addr_low + j * 0x1000) % sizeof(u32)*8);
        }
        break;
      default:
        serial_printf("Unknown memory type\r\n");
        break;
    }
  }

  initialized = true;
  return true;
}
/* Has the page frame allocator been initialized? */
bool page_frame_alloc_initialized(void) {
  return initialized;
}

/* Get a free page frame */
void *get_free_page_frame(void) {
  for (u32 i = 0; i < 0x100000000/(0x1000*sizeof(u32)*8); i++) {
    if (physical_bitmap[i] == 0xffffffff) continue;
    for (u32 j = 0; j < 0x1000; j++) {
      if (physical_bitmap[i] & (1 << j)) continue;
      physical_bitmap[i] |= 1 << j;
      return PTR_U32(i*0x1000*sizeof(u32)*8 + j*0x1000);
    }
  }
  return NULL;
}
/* Mark a page frame as free */
void page_frame_free(void *frame) {
  u32 index = U32_PTR(frame) / (0x1000*sizeof(u32)*8);
  u32 offset = (U32_PTR(frame) / 0x1000) % sizeof(u32)*8;
  physical_bitmap[index] &= ~(1 << offset);
}

/* Get the number of free pages */
u32 get_free_page_count(void) {
  u32 count = 0;
  for (u32 i = 0; i < 0x100000000/(0x1000*sizeof(u32)*8); i++) {
    if (physical_bitmap[i] == 0xffffffff) continue;
    for (u32 j = 0; j < 0x1000; j++) {
      if (physical_bitmap[i] & (1 << j)) continue;
      count++;
    }
  }
  return count;
}
