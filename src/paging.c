/* Implements paging.h */
#include "paging.h"

/* Flush a page that has recently been remapped */
void flush_page(uint32_t address) {
  __asm__ __volatile__ ("invlpg (%0)" : : "r" (address));
}
