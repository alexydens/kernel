/* Includes */
#include "vga_text_term.h"

/* Kernel entry point */
void kernel_main(void) {
  _vga_text_set_color(_VGA_TEXT_COLOR_WHITE, _VGA_TEXT_COLOR_DARK_GREY);
  _vga_text_set_cursor(0, 0);
  _vga_text_clear(0);
  _vga_text_puts("Hello, World!\r\n");
  while (1) {}
}
