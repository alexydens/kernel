/* Include guard */
#if !defined(GDT_H)
#define GDT_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

/* Flags enum */
enum gdt_flags {
  GDT_FLAGS_PAGEADDR = 8,       /* For 4KiB granularity */
  GDT_FLAGS_32BIT = 4,          /* For 32 rather than 16 bit code */
  GDT_FLAGS_LONGMODE = 2,       /* For long mode segment */
  GDT_FLAGS_RESERVED = 1        /* Reserved = ALWAYS 0 */
};

/* Access enum */
enum gdt_access {
  /* Is this valid mem? */
  GDT_ACCESS_PRESENT = 0x80,
  /* Highest privileges */
  GDT_ACCESS_RING0 = 0x00,
  /* Lowest privileges */
  GDT_ACCESS_RING3 = 0x60,
  /* Not a TSS segment or other system segment */
  GDT_ACCESS_NOTTSS = 0x10,
  /* Is executable */
  GDT_ACCESS_EXECUTABLE = 0x08,
  /* If executable, can a higher privilege execute */
  /* If not, does it grow down */
  GDT_ACCESS_DIR_CONF = 0x04,
  /* If executable, can it be read */
  /* If not, can it be written to */
  GDT_ACCESS_READWRITE = 0x02,
  /* CPU Set when segment accessed unless 1. 0 and GDT in RO = page fault */
  GDT_ACCESS_ACCESSED = 0x01,
  /* System segment types */
  GDT_ACCESS_SYS_TSS16A = 0x01,
  GDT_ACCESS_SYS_LDT = 0x02,
  GDT_ACCESS_SYS_TSS16B = 0x03,
  GDT_ACCESS_SYS_TSS32A = 0x09,
  GDT_ACCESS_SYS_TSS32B = 0x0B,
  GDT_ACCESS_SYS_LDT64 = 0x02,
  GDT_ACCESS_SYS_TSS64A = 0x0A,
  GDT_ACCESS_SYS_TSS64B = 0x0B
};

/* GDT Descriptor (GDTR) */
struct gdtr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

/* GDT Entry */
struct gdt_entry {
  uint16_t limit_0_15;
  uint16_t base_0_15;
  uint8_t base_16_23;
  uint8_t access;
  uint8_t limit_16_19: 4;
  uint8_t flags: 4;
  uint8_t base_24_31;
} __attribute__((packed));

/* Initializes the GDT */
extern void gdt_init(void);

#endif /* GDT_H */
