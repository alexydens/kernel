/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Checks */
#if defined(__linux__)
#error "Wrong OS!"
#endif
#if !defined(__i386__)
#error "Wrong architecture!"
#endif

/* Project includes */
#include "graphics_vga.h"

/* Entry point */
void kernel_main(void) {
  graphics_vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY);
  graphics_vga_clear(0);
  graphics_vga_set_cursor(0, 0);
  graphics_vga_puts("Hello, World!\r\n");
}
