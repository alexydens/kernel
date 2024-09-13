/* Implements gdt.h */
#include "gdt.h"

/* Globals */
struct gdtr gdtr;
struct gdt_entry gdt[3];

static inline struct gdt_entry create_gdtentry(
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t flags
) {
  return (struct gdt_entry) {
    .limit_0_15 = limit & 0xFFFF,
    .base_0_15 = base & 0xFFFF,
    .base_16_23 = (base >> 16) & 0xFF,
    .access = access,
    .limit_16_19 = (limit >> 16) & 0x0F,
    .flags = flags,
    .base_24_31 = (base >> 24) & 0xFF
  };
}

/* Initialize the GDT */
void gdt_init(void) {
  gdtr.base = (uint32_t)&gdt;
  gdtr.limit = sizeof(struct gdt_entry) * 3 - 1;
  gdt[0] = create_gdtentry(0, 0, 0, 0);
  gdt[1] = create_gdtentry(
      0,
      0xFFFFFF,
      GDT_ACCESS_PRESENT
        | GDT_ACCESS_RING0
        | GDT_ACCESS_NOTTSS
        | GDT_ACCESS_EXECUTABLE
        | GDT_ACCESS_DIR_CONF
        | GDT_ACCESS_READWRITE
        | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_PAGEADDR | GDT_FLAGS_32BIT
  );
  gdt[2] = create_gdtentry(
      0,
      0xFFFFFF,
      GDT_ACCESS_PRESENT
        | GDT_ACCESS_RING0
        | GDT_ACCESS_NOTTSS
        | GDT_ACCESS_READWRITE
        | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_PAGEADDR | GDT_FLAGS_32BIT
  );
  __asm__ __volatile__ ("lgdt %0" : : "m" (gdtr));

  __asm__ __volatile__ ("mov %cr0, %eax");
  __asm__ __volatile__ ("or $0x1, %eax");
  __asm__ __volatile__ ("mov %eax, %cr0");

  __asm__ __volatile__ ("ljmp $0x08, $1f");
  __asm__ __volatile__ ("1:");
}
