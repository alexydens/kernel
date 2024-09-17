#include <stdint.h>

void kernel_main(void) {
  volatile uint16_t *vga_buffer = (uint16_t *)0xc03ff000;
  vga_buffer[0] = 0xf041;
  vga_buffer[1] = 0xf042;
  while (1) {}
}
