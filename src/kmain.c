/* Includes */
#include <core/types.h>
#include <core/logging.h>
#include <ext/multiboot.h>
#include <ext/font8x8_basic.h>
#include <io/serial.h>
#include <io/vga_term.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/paging.h>

/* Entry point */
void kernel_main(u32 mb_info_addr) {
  /* Variables */
  multiboot_info_t *mb_info = (multiboot_info_t *)(mb_info_addr+0xc0000000);
  char str[256];

  /* Initialization */
  /* Initialize vga terminal */
#ifdef VGA_TERM_ENABLED
  /*vga_term_set_color(VGA_TERM_COLOR_GREEN, VGA_TERM_COLOR_BLACK);*/
  vga_term_set_color(VGA_TERM_COLOR_LIGHT_GREY, VGA_TERM_COLOR_BLUE);
  vga_term_set_cursor(0, 0);
  vga_term_clear(0);
  LOG("===> Initialized VGA Terminal\r\n");
#endif
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
  paging_init();
  LOG("===> Initialized Paging\r\n");

  /* Test */
  LOG("Framebuffer address: 0x");
  hex_str_32(mb_info->framebuffer_addr, str);
  LOG(str);
  LOG("\r\n");
  LOG("Framebuffer width: 0x");
  hex_str_32(mb_info->framebuffer_width, str);
  LOG(str);
  LOG("\r\n");
  LOG("Framebuffer height: 0x");
  hex_str_32(mb_info->framebuffer_height, str);
  LOG(str);
  LOG("\r\n");
  LOG("Framebuffer bits per pixel: 0x");
  hex_str_32(mb_info->framebuffer_bpp, str);
  LOG(str);
  LOG("\r\n");

  /* Remap framebuffer */
  for (u32 i = 0; i < 1024; i++) {
    map_page_frame(
        0xfd000000 + i * 0x1000,
        0xfd000000 + i * 0x1000,
        PTE_FLAGS_RW
        | PTE_FLAGS_PRESENT
    );
    flush_page(0xfd000000 + i * 0x1000);
  }
  for (u32 x = 0; x < 8; x++) {
    for (u32 y = 0; y < 8; y++) {
      if (font8x8_basic['A'][y] & (1 << x)) {
        ((u16 *)0xfd000000)[(x*4+0) + (y*4+0) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+1) + (y*4+0) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+2) + (y*4+0) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+3) + (y*4+0) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+0) + (y*4+1) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+1) + (y*4+1) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+2) + (y*4+1) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+3) + (y*4+1) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+0) + (y*4+2) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+1) + (y*4+2) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+2) + (y*4+2) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+3) + (y*4+2) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+0) + (y*4+3) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+1) + (y*4+3) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+2) + (y*4+3) * 1920] = 0xffff;
        ((u16 *)0xfd000000)[(x*4+3) + (y*4+3) * 1920] = 0xffff;
      }
    }
  }

  /* Hang when finished */
  __asm__ __volatile__ ("cli;hlt");
  while (1);
}
