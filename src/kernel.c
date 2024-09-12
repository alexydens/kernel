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
#include "gdt.h"
#include "idt.h"
#include "mem_paging.h"

/* Entry point */
void kernel_main(void) {
  graphics_vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY);
  graphics_vga_clear(0);
  graphics_vga_set_cursor(0, 0);
  graphics_vga_puts("===> VGA Mode 3 setup: DONE\r\n");
  graphics_vga_puts("===> Loading GDT: STARTING...\r\n");
  gdt_init();
  graphics_vga_puts("===> Loading GDT: DONE\r\n");
  graphics_vga_puts("===> Loading IDT: STARTING...\r\n");
  idt_init();
  graphics_vga_puts("===> Loading IDT: DONE\r\n");
  graphics_vga_puts("===> Loading PD and PTs: STARTING...\r\n");
  mem_paging_init();
  graphics_vga_puts("===> Loading PD and PTs: DONE...\r\n");
}
