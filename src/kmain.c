/* Includes */
#include <ext/multiboot.h>
#include <core/types.h>
#include <core/conf.h>

/* Entry point */
void kernel_main(unsigned int mb_info_addr) {
  /* Multiboot info */
  multiboot_info_t *mb_info = (multiboot_info_t *)PTR_U32(mb_info_addr);

  /* ----- INITIALIZATION ----- */
  /* Initialize serial ports */
  if (!serial_init()) __asm__ __volatile__ ("int $0x3");
  serial_puts("Hello, World!\n", SERIAL_PORT_COM1);

  /* ----- HALT ----- */
  /* Loop infinitely */
  while (1);
  /* This shouldn't run - clear interrupts and halt if it does */
  __asm__ __volatile__ ("cli;hlt");
  /* This signifies that this part of the code is never reached */
  __builtin_unreachable();
  /* Cast away any unused variables */
  (void)mb_info;
}
