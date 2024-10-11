/* Includes */
#include <ext/multiboot.h>
#include <core/types.h>
#include <core/conf.h>

/* Globals */
__attribute__((aligned(0x1000)))
u32 pt[1024];
__attribute__((aligned(0x1000)))
u32 pt2[1024];

/* Keyboard handler */
void keyboard_handler(irq_args_t *args) {
  /* Get the scancode */
  u8 scancode = port_inb(0x60);

  /* Print the scancode */
  //if (scancode & 0x80)
    //serial_printf("Key 0x%xb down\r\n", scancode & 0x7f);
  //else
    //serial_printf("Key 0x%xb up\r\n", scancode & 0x7f);

  /* Ignore */
  (void)args;
  (void)scancode;
}

/* Entry point */
void kernel_main(unsigned int mb_info_addr) {
  /* Multiboot info */
  multiboot_info_t *mb_info =
    (multiboot_info_t *)PTR_U32(mb_info_addr+0xc0000000);

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
  //add_irq_handler(1, keyboard_handler);
  serial_printf("===> Initialized IDT\r\n");
  /* Initialize page frame allocator */
  if (!page_frame_alloc_init(mb_info)) {
    serial_printf("ERROR: Failed to initialize page frame allocator!\r\n");
    __asm__ __volatile__ ("int $0x3");
  }
  serial_printf("===> Initialized page frame allocator\r\n");

  /* ----- TEST ----- */
  serial_printf("framebuffer_addr: 0x%xd\r\n", mb_info->framebuffer_addr);
  serial_printf("framebuffer_width: 0x%xd\r\n", mb_info->framebuffer_width);
  serial_printf("framebuffer_height: 0x%xd\r\n", mb_info->framebuffer_height);
  serial_printf("framebuffer_bpp: 0x%xd\r\n", mb_info->framebuffer_bpp);
  _init_PD[0x301] = (U32_PTR(pt) - 0xc0000000) | 0x00000003;
  _init_PD[0x302] = (U32_PTR(pt2) - 0xc0000000) | 0x00000003;
  for (u32 i = 0; i < 1024; i++) {
    pt[i] =
      (mb_info->framebuffer_addr + i * 0x1000) | 0x00000003;
  }
  for (u32 i = 0; i < 1024; i++) {
    pt2[i] =
      (mb_info->framebuffer_addr + i * 0x1000 + 1024 * 0x1000) | 0x00000003;
  }
  for (
      u32 i = 0;
      i < mb_info->framebuffer_width * mb_info->framebuffer_height;
      i++
  ) {
    ((u32*)0xc0400000)[i] = i;//0xffffffff;
  }

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
