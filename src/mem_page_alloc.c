/* Implements mem/page_alloc.h */
#include <mem/page_alloc.h>

/* Globals */
static u32 kernel_heap_bitmap[KERNEL_HEAP_SIZE / (PAGE_SIZE*sizeof(u32)*8)];
static u32 user_heap_bitmap[USER_HEAP_SIZE / (PAGE_SIZE*sizeof(u32)*8)];

/* Initialilze page allocator */
void page_alloc_init(void) {
  /* Initialize kernel heap */
  memset(kernel_heap_bitmap, 0, sizeof(kernel_heap_bitmap));
  /* Initialize user heap */
  memset(user_heap_bitmap, 0, sizeof(user_heap_bitmap));
}
/* Get num_pages free pages */
void *get_free_pages(u32 type, size_t num_pages) {
  switch (type) {
    case PAGE_TYPE_KERNEL_HEAP:
      /* Find first free num_pages bits in a row in the bitmap */
      for (size_t i = 0; i < KERNEL_HEAP_SIZE/(PAGE_SIZE*sizeof(u32)*8); i++) {
        if (kernel_heap_bitmap[i] == 0xffffffff) {
          continue;
        }
        /* The size and start of the current bits in a row */
        u32 size = 0;
        u32 start = 0;
        bool x = false;
        /* Check for num_pages '0' bits in a row */
        for (size_t j = 0; j < 32; j++) {
          if ((kernel_heap_bitmap[i] & (1 << j)) == 0) {
            if (!x)
              start = j;
            size++;
            if (size == num_pages) {
              /* Fill in the bitmap from start to start + size */
              for (size_t k = start; k < start + size; k++) {
                kernel_heap_bitmap[i] |= (1 << k);
              }
              /* Map and return the pages */
              u32 addr =
                i * (PAGE_SIZE*sizeof(u32)*8) + start * PAGE_SIZE;
              addr += VIRT_KERNEL_HEAP_START;
              return (void *)addr;
            }
            x = true;
          } else x = false;
        }
      }
      return NULL;
    case PAGE_TYPE_USER_HEAP:
      /* Find first free num_pages bits in a row in the bitmap */
      for (size_t i = 0; i < USER_HEAP_SIZE/(PAGE_SIZE*sizeof(u32)*8); i++) {
        if (user_heap_bitmap[i] == 0xffffffff) {
          continue;
        }
        /* The size and start of the current bits in a row */
        u32 size = 0;
        u32 start = 0;
        bool x = false;
        /* Check for num_pages '0' bits in a row */
        for (size_t j = 0; j < 32; j++) {
          if ((user_heap_bitmap[i] & (1 << j)) == 0) {
            if (!x)
              start = j;
            size++;
            if (size == num_pages) {
              /* Fill in the bitmap from start to start + size */
              for (size_t k = start; k < start + size; k++) {
                user_heap_bitmap[i] |= (1 << k);
              }
              /* Map and return the pages */
              u32 addr =
                i * (PAGE_SIZE*sizeof(u32)*8) + start * PAGE_SIZE;
              addr += VIRT_USER_HEAP_START;
              return (void *)addr;
            }
            x = true;
          } else x = false;
        }
      }
      return NULL;
    default:
      return NULL;
  }
}
/* Mark num_pages starting from addr as free */
void free_pages(u32 type, void *addr, size_t num_pages) {
  switch (type) {
    case PAGE_TYPE_KERNEL_HEAP:
      /* Fill in the bitmap from start to start + size */
      for (size_t i = 0; i < num_pages; i++) {
        u32 page_index = ((u32)addr + i * PAGE_SIZE - VIRT_KERNEL_HEAP_START);
        u32 row = page_index / (PAGE_SIZE*sizeof(u32)*8);
        u32 col = (page_index / PAGE_SIZE) % (sizeof(u32)*8);
        kernel_heap_bitmap[row] &= ~((u32)(1 << col));
      }
      break;
    case PAGE_TYPE_USER_HEAP:
      /* Fill in the bitmap from start to start + size */
      for (size_t i = 0; i < num_pages; i++) {
        u32 page_index = ((u32)addr + i * PAGE_SIZE - VIRT_USER_HEAP_START);
        u32 row = page_index / (PAGE_SIZE*sizeof(u32)*8);
        u32 col = (page_index / PAGE_SIZE) % (sizeof(u32)*8);
        char str[9];
        str[8] = 0;
        hex_str_32(user_heap_bitmap[row] & ~(1 << col), str);
        LOG("0x");
        LOG(str);
        LOG("\r\n");
        user_heap_bitmap[row] &= ~(1 << col);
      }
      break;
    default:
      break;
  }
}
/* Print 25 rows of the bitmap to the vga terminal */
void print_bitmap(u32 type) {
  switch (type) {
    case PAGE_TYPE_KERNEL_HEAP:
      for (size_t i = 0; i < 25; i++) {
        for (size_t j = 0; j < 32; j++)
          vga_term_putc(kernel_heap_bitmap[i] & (1 << j) ? '1' : '0');
        vga_term_puts("\r\n");
      }
      break;
    case PAGE_TYPE_USER_HEAP:
      for (size_t i = 0; i < 25; i++) {
        for (size_t j = 0; j < 32; j++)
          vga_term_putc(user_heap_bitmap[i] & (1 << j) ? '1' : '0');
        vga_term_puts("\r\n");
      }
      break;
    default:
      break;
  }
}
