/* Includes */
#include <core/base.h>

/* Entry point for the kernel */
void kernel_main(void) {
  /* Test */
  *(unsigned short *)0xc03ff000 = 'A' | (1 << 8);

  /* Halt */
  while (1);
  __asm__ __volatile__ ("cli;hlt");
}
