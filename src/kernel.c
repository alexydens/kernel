/* Includes */
#include "vga_text_term.h"
#include "gdt.h"
#include "idt.h"

/* Keyboard handler */
void keyboard_handler(irq_args_t *args) {
  /* Print message */
  vga_text_puts("Scancode: ");
  /* Get scancode */
  uint8_t scancode = port_inb(0x60);
  /* Print scancode */
  vga_text_putc('0' + (((scancode&0x7f) / 100) % 10));
  vga_text_putc('0' + (((scancode&0x7f) / 10) % 10));
  vga_text_putc('0' + ((scancode&0x7f) % 10));
  /* Print newline and if down/up */
  if (scancode & 0x80)
    vga_text_puts(" (up)\r\n");
  else
    vga_text_puts(" (down)\r\n");
}

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
  add_irq_handler(1, keyboard_handler);
  vga_text_puts("===> Initialized Interrupt Descriptor Table.\r\n");
  /* Test */
  __asm__ __volatile__ ("int $0x3");
  vga_text_puts("Hello world!\r\n");
  /* Loop */
  while (1) {}
}
