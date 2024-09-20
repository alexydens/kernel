/* Include guard */
#ifndef _GDT_H
#define _GDT_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Consts */
/* Access byte */
#define _GDT_ACCESS_PRESENT     (1 << 7)
#define _GDT_ACCESS_DPL0        (0 << 5)
#define _GDT_ACCESS_DPL1        (1 << 5)
#define _GDT_ACCESS_DPL2        (2 << 5)
#define _GDT_ACCESS_DPL3        (3 << 5)
#define _GDT_ACCESS_NOTSYS      (1 << 4)
/* Non-system segment access byte: continued */
#define _GDT_ACCESS_EXEC        (1 << 3)
#define _GDT_ACCESS_CONFORMS    (1 << 2)
#define _GDT_ACCESS_GROWDOWN    (1 << 2)
#define _GDT_ACCESS_READABLE    (1 << 1)
#define _GDT_ACCESS_WRITABLE    (1 << 1)
#define _GDT_ACCESS_ACCESSED    (1 << 0)
/* System segment access byte: continued */
/* Postfixes: A = available, B = busy */
#define _GDT_ACCESS_SYS_16TSSA  0x1
#define _GDT_ACCESS_SYS_LDT     0x2
#define _GDT_ACCESS_SYS_16TSSB  0x3
#define _GDT_ACCESS_SYS_32TSSA  0x9
#define _GDT_ACCESS_SYS_32TSSB  0xb
#define _GDT_ACCESS_SYS_64TSSA  0x9
#define _GDT_ACCESS_SYS_64TSSB  0xb
/* Flags */
#define _GDT_FLAGS_GRANULARITY  (1 << 3)
#define _GDT_FLAGS_32BIT        (1 << 2)
#define _GDT_FLAGS_16BIT        (0 << 2)
#define _GDT_FLAGS_64BIT        (1 << 1)

/* GDT Descriptor */
typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) _gdtr_t;

/* GDT Entry */
typedef struct {
  uint16_t  limit_low;
  uint16_t  base_low;
  uint8_t   base_middle;
  uint8_t   access;
  uint8_t   limit_middle: 4;
  uint8_t   flags:        4;
  uint8_t   base_high;
} __attribute__((packed)) _gdt_entry_t;

/* Create a gdt entry */
static inline _gdt_entry_t _gdt_entry(
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t flags) {
  _gdt_entry_t entry;
  entry.limit_low = limit & 0xffff;
  entry.base_low = base & 0xffff;
  entry.base_middle = (base >> 16) & 0xff;
  entry.access = access;
  entry.limit_middle = (limit >> 16) & 0x0f;
  entry.flags = flags;
  entry.base_high = (base >> 24) & 0xff;
  return entry;
}

/* Initialize the gdt */
extern void _gdt_init(void);

#endif /* _GDT_H */
