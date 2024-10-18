/* Includes */
#include <core/base.h>
#include <core/puttypes.h>
#include <core/printf.h>
#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <mem/pfa.h>
#include <ext/multiboot.h>

/* Entry point for the kernel */
void kernel_main(u32 mb_info_ptr) {
  /* Multiboot info */
  multiboot_info_t *mb_info = (multiboot_info_t *)(mb_info_ptr+0xc0000000);

  /* Initialize */
  if (!serial_init(12)) goto init_err;
  serial_printf("===> Initialized serial port I/O\r\n");
  if (!gdt_init()) goto init_err;
  serial_printf("===> Initialized Global Descriptor Table\r\n");
  if (!idt_init()) goto init_err;
  serial_printf("===> Initialized Interrupt Descriptor Table\r\n");
  if (!pfa_init(mb_info)) goto init_err;
  serial_printf("===> Initialized Page Frame Allocator\r\n");

  /* Test exceptions */
  //__asm__ __volatile__ ("int $0x3");
  //*(u32 *)0xdeadbeef = 0xdeadbeef;
  
  /* Test PFA */
  //u32 addr = pfa_get_frame();
  //serial_printf("Addr: 0x%08x\r\n", addr);
  //pfa_free_frame(addr);

  /* Halt */
  while (1);
  __asm__ __volatile__ (
      "cli\n\t"
      "1:\n\t"
      "hlt\n\t"
      "jmp 1b");

  /* Error */
  init_err:
  serial_printf("Initialization error!\r\n");
  __asm__ __volatile__ ("cli;hlt");
}
