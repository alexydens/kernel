/* Includes */
#include <core/types.h>
#include <ext/multiboot.h>
#include <io/serial.h>

/* Entry point */
void kernel_main(multiboot_info_t *mb_info) {
  /* Variables */

  /* Initialization */
  serial_configure(SERIAL_COM1);

  /* Testing */
  serial_send_str(SERIAL_COM1, "Hello, World!\n");

  /* Hang when finished */
  __asm__ __volatile__ ("cli;hlt");
  while (1);
  /* Stop compiler warning 'unused variable' */
  (void)mb_info;
}
