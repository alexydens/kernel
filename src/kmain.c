/* Includes */
#include <core/base.h>
#include <core/puttypes.h>
#include <core/printf.h>
#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <ext/multiboot.h>

/* A putc as required */
static inline void putc(u8 c) { serial_putc(c, SERIAL_PORT_COM1); }

/* Entry point for the kernel */
void kernel_main(u32 mb_info_ptr) {
  /* Multiboot info */
  multiboot_info_t *mb_info = (multiboot_info_t *)(mb_info_ptr+0xc0000000);

  /* Init */
  if (!serial_init(12)) __asm__ __volatile__ ("int $0x3");
  if (!gdt_init()) __asm__ __volatile__ ("int $0x3");
  if (!idt_init()) __asm__ __volatile__ ("int $0x3");

  /* Test */
  __asm__ __volatile__ ("int $0x3");
  _printf(putc, "Hex is: %08x\r\n", 0xea);
  _printf(putc, "Capital hex is: %08X\r\n", 0xdeadbeef);
  _printf(putc, "Int is: %+05d\r\n", 15);

  /* Print some info about the framebuffer */
  //serial_puts("framebuffer_addr: 0x", SERIAL_PORT_COM1);
  //put32hex(mb_info->framebuffer_addr, putc);
  //serial_puts("\r\n", SERIAL_PORT_COM1);
  //serial_puts("framebuffer_width: 0x", SERIAL_PORT_COM1);
  //put32hex(mb_info->framebuffer_width, putc);
  //serial_puts("\r\n", SERIAL_PORT_COM1);
  //serial_puts("framebuffer_height: 0x", SERIAL_PORT_COM1);
  //put32hex(mb_info->framebuffer_height, putc);
  //serial_puts("\r\n", SERIAL_PORT_COM1);
  //serial_puts("framebuffer_bpp: 0x", SERIAL_PORT_COM1);
  //put32hex(mb_info->framebuffer_bpp, putc);
  //serial_puts("\r\n", SERIAL_PORT_COM1);

  /* Halt */
  while (1);
  __asm__ __volatile__ (
      "cli\n\t"
      "1:\n\t"
      "hlt\n\t"
      "jmp 1b");
}
