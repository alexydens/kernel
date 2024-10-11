ENTRY(_start)

SECTIONS
{
  /* Physical addr of kernel: 0x00100000 */
  . = 0x0010000;
  /* Symbol for physical address of start of kernel */
  _phys_start_kernel = .;
  /* Data and text (physical) used for multiboot header and bootstrap code */
  .multiboot.data : {
    *(.multiboot.data)
  }
  .multiboot.text : {
    *(.multiboot.text)
  }

  /* Virtual addr of kernel: 0xC0100000 */
  . += 0xC0000000;

  /* Symbol for start of kernel */
  _start_kernel = .;

  /* Text */
  .text ALIGN(4K) : AT (ADDR (.text) - 0xC0000000) {
    *(.text)
  }
  /* Read only data */
  .rodata ALIGN(4K) : AT (ADDR (.rodata) - 0xC0000000) {
    *(.rodata)
  }
  /* Data */
  .data ALIGN(4K) : AT (ADDR (.data) - 0xC0000000) {
    *(.data)
  }
  /* Block starting symbol (variable data of fixed size) */
  .bss ALIGN(4K) : AT (ADDR (.bss) - 0xC0000000) {
    *(COMMON)
    *(.bss)
    *(.init_stack)
  }

  /* Symbol for end of kernel */
  _end_kernel = .;
  _phys_end_kernel = . - 0xc0000000;
}
