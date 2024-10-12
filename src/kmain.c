/* Includes */
#include <core/base.h>
#include <misc/gdt.h>

/* Entry point for the kernel */
void kernel_main(void) {
  /* Init */
  if (!gdt_init()) __asm__ __volatile__ ("int $0x3;");

  /* Test */
  *(unsigned short *)0xc03ff000 = 'A' | (1 << 8);

  /* Halt */
  while (1);
  __asm__ __volatile__ ("cli;hlt");
}
