/* Includes */
#include <core/types.h>
#include <ext/multiboot.h>
#include <io/serial.h>
#include <io/vga_term.h>

/* Entry point */
void kernel_main(multiboot_info_t *mb_info) {
  /* Variables */

  /* Initialization */
  /* Initialize serial port 1 */
  serial_configure(SERIAL_COM1);
  /* Initialize vga terminal */
  /*vga_term_set_color(VGA_TERM_COLOR_GREEN, VGA_TERM_COLOR_BLACK);*/
  vga_term_set_color(VGA_TERM_COLOR_LIGHT_GREY, VGA_TERM_COLOR_BLUE);
  vga_term_set_cursor(0, 0);
  vga_term_clear(0);

  /* Testing */
  serial_send_str(SERIAL_COM1, "Hello, World!\n");
  vga_term_puts("Hello, World!\r\n");

  /* Hang when finished */
  __asm__ __volatile__ ("cli;hlt");
  while (1);
  /* Stop compiler warning 'unused variable' */
  (void)mb_info;
}
