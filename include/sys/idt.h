/* Include guard */
#ifndef _SYS_IDT_H
#define _SYS_IDT_H

/* Implements the interrupt handling for the kernel */

/* Includes */
#include <core/types.h>
#include <core/logging.h>
#include <sys/gdt.h>
#include <io/port.h>

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
  u16 limit;
  u32 base;
} __attribute__((packed)) idtr_t;

/* IDT Entry */
typedef struct {
	u16    isr_0_15;     /* Lower 16 bits of ISR */
	u16    segment;      /* Segment of ISR */
	u8     reserved;     /* Always 0 */
	u8     flags;        /* flags */
	u16    isr_16_31;    /* The higher 16 bits of the ISR's address */
} __attribute__((packed)) idt_entry_t;

/* Arguments passed to IRQ handlers */
typedef struct {
  /* The irq num starts at 0 for irq0 */
  /* The interrupt num starts at 32 for irq0 */
  u32 interrupt_number, irq_number;
  u32 eip, cs, eflags;
  u32 esp, ss;
} irq_args_t;
/* Callback for an IRQ */
typedef void (*irq_handler_t)(irq_args_t *args);

/* Create IDT entry */
static inline idt_entry_t idt_entry(
    u32 handler,
    u16 segment,
    u8 flags) {
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
extern void add_irq_handler(u8 irq, irq_handler_t handler);

#endif /* _SYS_IDT_H */
