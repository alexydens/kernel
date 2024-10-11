/* Implements sys/gdt.h */
#include <sys/gdt.h>

/* Consts */
/* Access byte */
#define GDT_ACCESS_PRESENT     (1 << 7)
#define GDT_ACCESS_DPL0        (0 << 5)
#define GDT_ACCESS_DPL1        (1 << 5)
#define GDT_ACCESS_DPL2        (2 << 5)
#define GDT_ACCESS_DPL3        (3 << 5)
#define GDT_ACCESS_NOTSYS      (1 << 4)
/* Non-system segment access byte: continued */
#define GDT_ACCESS_EXEC        (1 << 3)
#define GDT_ACCESS_CONFORMS    (1 << 2)
#define GDT_ACCESS_GROWDOWN    (1 << 2)
#define GDT_ACCESS_READABLE    (1 << 1)
#define GDT_ACCESS_WRITABLE    (1 << 1)
#define GDT_ACCESS_ACCESSED    (1 << 0)
/* System segment access byte: continued */
/* Postfixes: A = available, B = busy */
#define GDT_ACCESS_SYS_16TSSA  0x1
#define GDT_ACCESS_SYS_LDT     0x2
#define GDT_ACCESS_SYS_16TSSB  0x3
#define GDT_ACCESS_SYS_32TSSA  0x9
#define GDT_ACCESS_SYS_32TSSB  0xb
#define GDT_ACCESS_SYS_64TSSA  0x9
#define GDT_ACCESS_SYS_64TSSB  0xb
/* Flags */
#define GDT_FLAGS_GRANULARITY  (1 << 3)
#define GDT_FLAGS_32BIT        (1 << 2)
#define GDT_FLAGS_16BIT        (0 << 2)
#define GDT_FLAGS_64BIT        (1 << 1)

/* GDT Descriptor */
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdtr_t;

/* GDT Entry */
typedef struct {
  u16  limit_low;
  u16  base_low;
  u8   base_middle;
  u8   access;
  u8   limit_middle: 4;
  u8   flags:        4;
  u8   base_high;
} __attribute__((packed)) gdt_entry_t;

/* Create a gdt entry */
static inline gdt_entry_t gdt_entry(
    u32 base,
    u32 limit,
    u8 access,
    u8 flags) {
  gdt_entry_t entry;
  entry.limit_low = limit & 0xffff;
  entry.base_low = base & 0xffff;
  entry.base_middle = (base >> 16) & 0xff;
  entry.access = access;
  entry.limit_middle = (limit >> 16) & 0x0f;
  entry.flags = flags;
  entry.base_high = (base >> 24) & 0xff;
  return entry;
}

/* Globals */
static bool initialized = false;
__attribute__((aligned(0x1000)))
static gdtr_t gdt;
__attribute__((aligned(0x1000)))
static gdt_entry_t gdt_entries[5];

/* Initialize GDT (return false on error) */
bool gdt_init(void) {
  /* Populate GDTR */
  gdt.limit = sizeof(gdt_entries) - 1;
  gdt.base = U32_PTR(&gdt_entries);

  /* Populate GDT entries */
  /* Null entry */
  gdt_entries[0] = gdt_entry(0, 0, 0, 0);
  /* Code segment - kernel */
  gdt_entries[1] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_CONFORMS
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Data segment - kernel */
  gdt_entries[2] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Code segment - user */
  gdt_entries[3] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_CONFORMS
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Data segment - user */
  gdt_entries[4] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );

  /* Load GDT */
  __asm__ __volatile__ ("lgdt %0" : : "m" (gdt));

  /* Enable protected mode */
  __asm__ __volatile__ ("mov %cr0, %eax");
  __asm__ __volatile__ ("or $0x1, %eax");
  __asm__ __volatile__ ("mov %eax, %cr0");

  /* Load the segment registers */
  __asm__ __volatile__ ("mov $0x10, %ax");
  __asm__ __volatile__ ("mov %ax, %cs");
  __asm__ __volatile__ ("mov %ax, %ds");
  __asm__ __volatile__ ("mov %ax, %es");
  __asm__ __volatile__ ("mov %ax, %fs");
  __asm__ __volatile__ ("mov %ax, %gs");
  __asm__ __volatile__ ("mov %ax, %ss");

  /* Jump to 32-bit protected mode */
  __asm__ __volatile__ ("ljmp $0x08, $1f");
  __asm__ __volatile__ ("1:");

  initialized = true;
  return true;
}
/* Has the GDT been initialized? */
bool gdt_initialized(void) {
  return initialized;
}
