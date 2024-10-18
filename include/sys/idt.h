/* Include guard */
#ifndef SYS_IDT_H
#define SYS_IDT_H

/* Includes */
#include <core/base.h>
#include <core/puttypes.h>
#include <io/port.h>
#include <io/serial.h>
#include <sys/gdt.h>

/* The arguments passed to exception handlers */
struct isr_args {
  u32 interrupt_number, error_code;
  u32 eip, cs, eflags;
  u32 esp, ss;
};

/* Initialize the IDT */
extern bool idt_init(void);

#endif /* SYS_IDT_H */
