/* Include guard */
#ifndef _SYS_IDT_H
#define _SYS_IDT_H

/* Implements the interrupt handling for the kernel */

/* Includes */
#include <core/types.h>
#include <io/serial.h>
#include <io/port.h>
#include <sys/gdt.h>

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

/* Initializes the IDT (return false on error) */
extern bool idt_init(void);
/* Has the IDT been initialized? */
extern bool idt_initialized(void);

/* Add IRQ handler */
extern void add_irq_handler(u8 irq, irq_handler_t handler);

#endif /* _SYS_IDT_H */
