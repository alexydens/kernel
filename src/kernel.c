/* Includes */
#include "gdt.h"
#include "vga_text_term.h"

/* Kernel entry point */
void kernel_main(void) {
  /* Initialize GDT */
  _gdt_init();
  /* Initialize vga text terminal */
  _vga_text_set_color(_VGA_TEXT_COLOR_WHITE, _VGA_TEXT_COLOR_DARK_GREY);
  _vga_text_set_cursor(0, 0);
  _vga_text_clear(0);
  _vga_text_puts("===> Initialized Global Descriptor Table.\r\n");
  _vga_text_puts("===> Initialized VGA Text Mode Terminal.\r\n");
  /* Test */
  _vga_text_puts("Hello world!\r\n");
  /* Loop */
  while (1) {}
}
