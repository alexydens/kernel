/* Includes */
#include <core/types.h>
#include <core/logging.h>
#include <ext/multiboot.h>
#include <io/serial.h>
#include <io/vga_term.h>
#include <sys/gdt.h>
#include <sys/idt.h>

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
  /* Initialize Global Descriptor Table */
  gdt_init();
  LOG("===> Initialized Global Descriptor Table\r\n");
  /* Initialize Interrupt Descriptor Table */
  idt_init();
  LOG("===> Initialized Interrupt Descriptor Table\r\n");

  /* Testing */
  LOG("Hello world!\r\n");
  __asm__ __volatile__ ("int $0x3");

  /* Hang when finished */
  __asm__ __volatile__ ("cli;hlt");
  while (1);
  /* Stop compiler warning 'unused variable' */
  (void)mb_info;
}
