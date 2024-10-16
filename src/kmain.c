/* Includes */
#include <core/base.h>
#include <core/puttypes.h>
#include <core/printf.h>
#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <ext/multiboot.h>

/* Entry point for the kernel */
void kernel_main(u32 mb_info_ptr) {
  /* Multiboot info */
  multiboot_info_t *mb_info = (multiboot_info_t *)(mb_info_ptr+0xc0000000);

  /* Init */
  if (!serial_init(12)) __asm__ __volatile__ ("int $0x3");
  if (!gdt_init()) __asm__ __volatile__ ("int $0x3");
  if (!idt_init()) __asm__ __volatile__ ("int $0x3");

  /* Test exceptions */
  //__asm__ __volatile__ ("int $0x3");
  //*(u32 *)0xdeadbeef = 0xdeadbeef;

  /* Print some info about the framebuffer */
  serial_printf("framebuffer_addr: 0x%08x\r\n", mb_info->framebuffer_addr);
  serial_printf("framebuffer_width: 0x%08x\r\n", mb_info->framebuffer_width);
  serial_printf("framebuffer_height: 0x%08x\r\n", mb_info->framebuffer_height);
  serial_printf("framebuffer_bpp: 0x%08x\r\n", mb_info->framebuffer_bpp);

  /* Halt */
  while (1);
  __asm__ __volatile__ (
      "cli\n\t"
      "1:\n\t"
      "hlt\n\t"
      "jmp 1b");
}
