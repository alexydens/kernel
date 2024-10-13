/* Implements sys/gdt.h */
#include <sys/gdt.h>

/* Consts */
/* Number of GDT entries */
#define GDT_ENTRIES            5
/* Access byte */
#define GDT_ACCESS_PRESENT     (1 << 7) /* Is this segment present? */
#define GDT_ACCESS_RING0       (0 << 5) /* DPL = 0 */
#define GDT_ACCESS_RING1       (1 << 5) /* DPL = 1 */
#define GDT_ACCESS_RING2       (2 << 5) /* DPL = 2 */
#define GDT_ACCESS_RING3       (3 << 5) /* DPL = 3 */
#define GDT_ACCESS_SYSSEG      (0 << 4) /* Is this a system segment? */
#define GDT_ACCESS_NOTSYS      (1 << 4) /* Is this a code/data segment? */
#define GDT_ACCESS_CODE        (1 << 3) /* Is this a code segment? */
#define GDT_ACCESS_DATA        (0 << 3) /* Is this a data segment? */
#define GDT_ACCESS_DIRECTION   (1 << 2) /* Does this segment grow down? */
#define GDT_ACCESS_CONFORMING  (1 << 2) /* Can lower DPLs jump to this seg? */
#define GDT_ACCESS_READABLE    (1 << 1) /* Is this code segment readable? */
#define GDT_ACCESS_WRITABLE    (1 << 1) /* Is this data segment writable? */
#define GDT_ACCESS_ACCESSED    (1 << 0) /* Has this segment been accessed? */
/* System segment type */
#define GDT_SYSSEG_TSS16A      (0x1)    /* 16-bit TSS (available) */
#define GDT_SYSSEG_LDT         (0x2)    /* LDT */
#define GDT_SYSSEG_TSS16B      (0x3)    /* 16-bit TSS (busy) */
#define GDT_SYSSEG_TSS32A      (0x9)    /* 32-bit TSS (available) */
#define GDT_SYSSEG_TSS32B      (0xB)    /* 32-bit TSS (busy) */
/* Long mode system segment type - LDT can also be used */
#define GDT_SYSSEG_TSS64A      (0x9)    /* 64-bit TSS (available) */
#define GDT_SYSSEG_TSS64B      (0xB)    /* 64-bit TSS (busy) */
/* Flags nibble */
#define GDT_FLAGS_GRANULARITY  (1 << 3) /* Page granularity? */
#define GDT_FLAGS_32BIT        (1 << 2) /* Is this segment in 32 bit mode? */
#define GDT_FLAGS_16BIT        (0 << 2) /* Is this segment in 16 bit mode? */
#define GDT_FLAGS_64BIT        (1 << 1) /* Is this segment in 64 bit mode? */

/* The GDT entry structure */
struct __packed gdt_entry {
  u16 limit_low;
  u16 base_low;
  u8 base_middle;
  u8 access;
  u8 limit_high: 4;
  u8 flags: 4;
  u8 base_high;
};

/* The GDT Descritptor structure */
struct __packed gdtr {
  u16 limit;
  u32 base;
};

/* Globals */
static struct gdtr gdtr __aligned(0x10);
static struct gdt_entry gdt[256] __aligned(0x10);

/* Utility functions */
static inline void set_entry(
    u32 index,
    u32 base,
    u32 limit,
    u8 access,
    u8 flags
) {
  gdt[index].base_low = base & 0xFFFF;
  gdt[index].base_middle = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;
  gdt[index].limit_low = limit & 0xFFFF;
  gdt[index].limit_high = (limit >> 16) & 0x0F;
  gdt[index].access = access;
  gdt[index].flags = flags;
}

/* Initialize the GDT */
bool gdt_init(void) {
  /* Set all entries to 0 */
  memset(gdt, 0, sizeof(gdt));

  /* Set the null entry */
  set_entry(0, 0, 0, 0, 0);

  /* Set the kernel code entry */
  set_entry(
      1,
      0x00000000,
      0xFFFFFFFF,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_CODE
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Set the kernel data entry */
  set_entry(
      2,
      0x00000000,
      0xFFFFFFFF,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_DATA
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );

  /* Set the user code entry */
  set_entry(
      3,
      0x00000000,
      0xFFFFFFFF,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_CODE
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Set the user data entry */
  set_entry(
      4,
      0x00000000,
      0xFFFFFFFF,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_RING3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_DATA
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );

  /* Set the GDT limit */
  gdtr.limit = 8*GDT_ENTRIES - 1;
  /* Set the GDT base */
  gdtr.base = (u32)&gdt;

  /* Load the GDT */
  __asm__ __volatile__ ("lgdt %0" : : "m" (gdtr));

  /* Reload the segment registers */
  __asm__ __volatile__ ("mov %0, %%ax" : : "r" (GDT_SEGMENT_KERNELDATA));
  __asm__ __volatile__ ("mov %ax, %ds");
  __asm__ __volatile__ ("mov %ax, %es");
  __asm__ __volatile__ ("mov %ax, %fs");
  __asm__ __volatile__ ("mov %ax, %gs");
  __asm__ __volatile__ ("mov %ax, %ss");

  /* Long jump to set cs */
  __asm__ __volatile__ ("ljmp $0x08, $1f");
  __asm__ __volatile__ ("1:");

  return true;
}
