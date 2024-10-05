/* Includes */
#include <core/types.h>
#include <core/logging.h>
#include <ext/multiboot.h>
#include <io/serial.h>
#include <io/vga_term.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/paging.h>
#include <mem/page_alloc.h>

/* Entry point */
void kernel_main(u32 mb_info_addr) {
  /* Variables */
  multiboot_info_t *mb_info = (multiboot_info_t *)(mb_info_addr+0xc0000000);

  /* Initialization */
  /* Initialize vga terminal */
  /*vga_term_set_color(VGA_TERM_COLOR_GREEN, VGA_TERM_COLOR_BLACK);*/
  vga_term_set_color(VGA_TERM_COLOR_LIGHT_GREY, VGA_TERM_COLOR_BLUE);
  vga_term_set_cursor(0, 0);
  vga_term_clear(0);
  LOG("===> Initialized VGA Terminal\r\n");
  /* Initialize serial port 1 */
  serial_configure(SERIAL_COM1);
  LOG("===> Initialized Serial Port: COM1\r\n");
  /* Initialize Global Descriptor Table */
  gdt_init();
  LOG("===> Initialized Global Descriptor Table\r\n");
  /* Initialize Interrupt Descriptor Table */
  idt_init();
  LOG("===> Initialized Interrupt Descriptor Table\r\n");
  /* Initialize paging */
  paging_init(mb_info);
  LOG("===> Initialized Paging\r\n");
  /* Initialize page allocator */
  page_alloc_init();
  LOG("===> Initialized Page Allocator\r\n");
  
  /* Hang when finished */
  while (1);
  __asm__ __volatile__ ("cli;hlt");
}
