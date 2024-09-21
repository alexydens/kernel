/* Includes */
#include "vga_text_term.h"
#include "gdt.h"
#include "idt.h"

/* Kernel entry point */
void kernel_main(void) {
  /* Initialize GDT */
  gdt_init();
  /* Initialize vga text terminal */
  vga_text_set_color(VGA_TEXT_COLOR_WHITE, VGA_TEXT_COLOR_DARK_GREY);
  vga_text_set_cursor(0, 0);
  vga_text_clear(0);
  vga_text_puts("===> Initialized Global Descriptor Table.\r\n");
  vga_text_puts("===> Initialized VGA Text Mode Terminal.\r\n");
  /* Initialize IDT */
  idt_init();
  vga_text_puts("===> Initialized Interrupt Descriptor Table.\r\n");
  /* Test */
  __asm__ __volatile__ ("int $0x3");
  vga_text_puts("Hello world!\r\n");
  /* Loop */
  while (1) {}
}
