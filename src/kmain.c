/* Includes */
#include <ext/multiboot.h>
#include <core/types.h>
#include <core/conf.h>

/* Keyboard handler */
void keyboard_handler(irq_args_t *args) {
  /* Get the scancode */
  u8 scancode = port_inb(0x60);

  /* Print the scancode */
  if (scancode & 0x80)
    serial_printf("Key 0x%xb down\r\n", scancode & 0x7f);
  else
    serial_printf("Key 0x%xb up\r\n", scancode & 0x7f);

  /* Ignore */
  (void)args;
}

/* Entry point */
void kernel_main(unsigned int mb_info_addr) {
  /* Multiboot info */
  multiboot_info_t *mb_info = (multiboot_info_t *)PTR_U32(mb_info_addr);

  /* ----- INITIALIZATION ----- */
  /* Initialize serial ports */
  if (!serial_init()) __asm__ __volatile__ ("int $0x3");
  serial_printf("===> Initialized serial ports\r\n");
  /* Initialize global descriptor table */
  if (!gdt_init()) {
    serial_printf("ERROR: Failed to initialize GDT!\r\n");
    __asm__ __volatile__ ("int $0x3");
  }
  serial_printf("===> Initialized GDT\r\n");
  /* Initialize interrupt descriptor table */
  if (!idt_init()) {
    serial_printf("ERROR: Failed to initialize IDT!\r\n");
    __asm__ __volatile__ ("int $0x3");
  }
  /* Add keyboard handler */
  add_irq_handler(1, keyboard_handler);
  serial_printf("===> Initialized IDT\r\n");

  /* ----- TEST ----- */
  serial_printf("Hello, world!\r\n");

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
