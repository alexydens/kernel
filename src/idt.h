/* Include guard */
#ifndef _IDT_H
#define _IDT_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include "gdt.h"

/* Consts */
/* IDT Entry flags */
#define IDT_FLAGS_PRESENT     (1 << 7)
#define IDT_FLAGS_RING0       (0 << 5)
#define IDT_FLAGS_RING1       (1 << 5)
#define IDT_FLAGS_RING2       (2 << 5)
#define IDT_FLAGS_RING3       (3 << 5)
#define IDT_FLAGS_TYPE_TASK   (0x5)
#define IDT_FLAGS_TYPE_IG16   (0x6)
#define IDT_FLAGS_TYPE_IG32   (0xE)
#define IDT_FLAGS_TYPE_TG16   (0x7)
#define IDT_FLAGS_TYPE_TG32   (0xF)
/* PIC ports */
#define PIC1_COMMAND_PORT     (0x20)
#define PIC1_DATA_PORT        (0x21)
#define PIC2_COMMAND_PORT     (0xA0)
#define PIC2_DATA_PORT        (0xA1)
/* PIC commmands */
#define PIC_COMMAND_INIT      (0x11)
#define PIC_COMMAND_ACK       (0x20)

/* IDT Descriptor */
typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idtr_t;

/* IDT Entry */
typedef struct {
	uint16_t    isr_0_15;     /* Lower 16 bits of ISR */
	uint16_t    segment;      /* Segment of ISR */
	uint8_t     reserved;     /* Always 0 */
	uint8_t     flags;        /* flags */
	uint16_t    isr_16_31;    /* The higher 16 bits of the ISR's address */
} __attribute__((packed)) idt_entry_t;

/* Arguments passed to IRQ handlers */
typedef struct {
  /* The irq num starts at 0 for irq0 */
  /* The interrupt num starts at 32 for irq0 */
  uint32_t interrupt_number, irq_number;
  uint32_t eip, cs, eflags;
  uint32_t esp, ss;
} irq_args_t;

/* Create IDT entry */
static inline idt_entry_t idt_entry(
    uint32_t handler,
    uint16_t segment,
    uint8_t flags) {
  idt_entry_t entry;
  entry.isr_0_15 = handler & 0xFFFF;
  entry.isr_16_31 = (handler >> 16) & 0xFFFF;
  entry.segment = segment;
  entry.reserved = 0;
  entry.flags = flags;
  return entry;
}

/* Initializes the IDT */
extern void idt_init(void);
/* Add IRQ handler */
extern void add_irq_handler(uint8_t irq, void *handler);

#endif /* _IDT_H */
