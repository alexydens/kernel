#if !defined(IDT_H)
#define IDT_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "graphics_vga.h"
#include "utils.h"

/* IDT Descriptor */
struct idtr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

/* IDT Entry */
struct idt_entry {
	uint16_t    isr_0_15;     /* Lower 16 bits of ISR */
	uint16_t    segment;      /* Segment of ISR */
	uint8_t     reserved;     /* Always 0 */
	uint8_t     flags;        /* flags */
	uint16_t    isr_16_31;    /* The higher 16 bits of the ISR's address */
} __attribute__((packed));

/* Initializes the IDT */
extern void idt_init(void);

#endif /* IDT_H */
