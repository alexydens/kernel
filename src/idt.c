/* Implements idt.h */
#include "idt.h"

/* Macros */
#define ADD_ISR_GATE(num) idt_set_gate(\
    num,\
    (uint32_t)_isr_##num,\
    GDT_SEGMENT_CODE,\
    IDT_FLAGS_PRESENT | IDT_FLAGS_RING0 | IDT_FLAGS_TYPE_IG32)
#define ADD_IRQ_GATE(num) idt_set_gate(\
    num+32,\
    (uint32_t)_irq_##num,\
    GDT_SEGMENT_CODE,\
    IDT_FLAGS_PRESENT | IDT_FLAGS_RING0 | IDT_FLAGS_TYPE_IG32)

/* Consts */
char *iterrupt_names[] = {
  "Division by zero",
  "Single-step interrupt",
  "Non maskable interrupt",
  "Breakpoint",
  "Overflow",
  "Bound range exceeded",
  "Invalid opcode",
  "Coprocessor not available",
  "Double fault",
  "Coprocessor segment overrun",
  "Invalid Task State Segment",
  "Segment not present",
  "Stack segment fault",
  "General protection fault",
  "Page fault",
  "Reserved",
  "x87 floating point exception",
  "Alignment check",
  "Machine check",
  "SIMD floating point exception",
  "Virtualization exception",
  "Control protection exception",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Hypervisor injection exception",
  "VMM communication exception",
  "Security exception",
  "Reserved"
};

/* Globals */
static idtr_t idtr;
static idt_entry_t entries[256];
static void (*irq_callbacks[16])(irq_args_t*);

#include "vga_text_term.h"
/* Generic isr handler */
struct isr_args {
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags;
  uint32_t esp, ss;
};
void isr_handler_common(struct isr_args *args) {
  /* Print the interrupt name */
  vga_text_puts("Interrupt: ");
  vga_text_puts(iterrupt_names[args->interrupt_number]);
  vga_text_puts("\r\n");
}
/* Generic irq handler */
void irq_handler_common(irq_args_t *args) {
  /* Print the irq number */
  /*vga_text_puts("IRQ: ");
  vga_text_putc('0' + (args->irq_number / 10));
  vga_text_putc('0' + (args->irq_number % 10));
  vga_text_puts("\r\n");*/

  /* Call the irq callback */
  if (irq_callbacks[args->irq_number])
    irq_callbacks[args->irq_number](args);

  /* Acknowledge the interrupt */
  if (args->irq_number < 8)
    port_outb(PIC1_COMMAND_PORT, PIC_COMMAND_ACK);
  else
    port_outb(PIC2_COMMAND_PORT, PIC_COMMAND_ACK);
}

/* First 22 ISRs */
extern void _isr_0(void);
extern void _isr_1(void);
extern void _isr_2(void);
extern void _isr_3(void);
extern void _isr_4(void);
extern void _isr_5(void);
extern void _isr_6(void);
extern void _isr_7(void);
extern void _isr_8(void);
extern void _isr_9(void);
extern void _isr_10(void);
extern void _isr_11(void);
extern void _isr_12(void);
extern void _isr_13(void);
extern void _isr_14(void);
extern void _isr_15(void);
extern void _isr_16(void);
extern void _isr_17(void);
extern void _isr_18(void);
extern void _isr_19(void);
extern void _isr_20(void);
extern void _isr_21(void);
extern void _isr_22(void);
extern void _isr_23(void);
extern void _isr_24(void);
extern void _isr_25(void);
extern void _isr_26(void);
extern void _isr_27(void);
extern void _isr_28(void);
extern void _isr_29(void);
extern void _isr_30(void);
extern void _isr_31(void);
extern void _irq_0(void);
extern void _irq_1(void);
extern void _irq_2(void);
extern void _irq_3(void);
extern void _irq_4(void);
extern void _irq_5(void);
extern void _irq_6(void);
extern void _irq_7(void);
extern void _irq_8(void);
extern void _irq_9(void);
extern void _irq_10(void);
extern void _irq_11(void);
extern void _irq_12(void);
extern void _irq_13(void);
extern void _irq_14(void);
extern void _irq_15(void);

/* Set IDT entry */
static inline void idt_set_gate(
    uint8_t index,
    uint32_t handler,
    uint16_t segment,
    uint8_t flags) {
  entries[index].isr_0_15 = handler & 0xFFFF;
  entries[index].isr_16_31 = (handler >> 16) & 0xFFFF;
  entries[index].segment = segment;
  entries[index].reserved = 0;
  entries[index].flags = flags;
}

/* Initializes the IDT */
void idt_init(void) {
  /* Setupt IDTR */
  idtr.limit = sizeof(idt_entry_t) * 256 - 1;
  idtr.base = (uint32_t)&entries;

  /* Clear IDT */
  memset(entries, 0, sizeof(idt_entry_t) * 256);

  /* Add Interrupt Gates */
  ADD_ISR_GATE(0);
  ADD_ISR_GATE(1);
  ADD_ISR_GATE(2);
  ADD_ISR_GATE(3);
  ADD_ISR_GATE(4);
  ADD_ISR_GATE(5);
  ADD_ISR_GATE(6);
  ADD_ISR_GATE(7);
  ADD_ISR_GATE(8);
  ADD_ISR_GATE(9);
  ADD_ISR_GATE(10);
  ADD_ISR_GATE(11);
  ADD_ISR_GATE(12);
  ADD_ISR_GATE(13);
  ADD_ISR_GATE(14);
  ADD_ISR_GATE(15);
  ADD_ISR_GATE(16);
  ADD_ISR_GATE(17);
  ADD_ISR_GATE(18);
  ADD_ISR_GATE(19);
  ADD_ISR_GATE(20);
  ADD_ISR_GATE(21);
  ADD_ISR_GATE(22);
  ADD_ISR_GATE(23);
  ADD_ISR_GATE(24);
  ADD_ISR_GATE(25);
  ADD_ISR_GATE(26);
  ADD_ISR_GATE(27);
  ADD_ISR_GATE(28);
  ADD_ISR_GATE(29);
  ADD_ISR_GATE(30);
  ADD_ISR_GATE(31);

  /* Remap the Programmable Interrupts Controller (PIC) */
  port_outb(PIC1_COMMAND_PORT, PIC_COMMAND_INIT);
  port_outb(PIC2_COMMAND_PORT, PIC_COMMAND_INIT);
  port_outb(PIC1_DATA_PORT, 0x20);  /* PIC1 = 32-40 */
  port_outb(PIC2_DATA_PORT, 0x28);  /* PIC2 = 40-48 */
  port_outb(PIC1_DATA_PORT, 0x04);  /* PIC2 Links to PIC1 on IRQ2 */
  port_outb(PIC2_DATA_PORT, 0x02);  /* PIC2 is secondary */
  port_outb(PIC1_DATA_PORT, 0x01);  /* 8086 mode */
  port_outb(PIC2_DATA_PORT, 0x01);  /* 8086 mode */
  port_outb(PIC1_DATA_PORT, 0x00);  /* Enable all IRQs */
  port_outb(PIC2_DATA_PORT, 0x00);  /* Enable all IRQs */

  /* Add interrupt gates */
  ADD_IRQ_GATE(0);
  ADD_IRQ_GATE(1);
  ADD_IRQ_GATE(2);
  ADD_IRQ_GATE(3);
  ADD_IRQ_GATE(4);
  ADD_IRQ_GATE(5);
  ADD_IRQ_GATE(6);
  ADD_IRQ_GATE(7);
  ADD_IRQ_GATE(8);
  ADD_IRQ_GATE(9);
  ADD_IRQ_GATE(10);
  ADD_IRQ_GATE(11);
  ADD_IRQ_GATE(12);
  ADD_IRQ_GATE(13);
  ADD_IRQ_GATE(14);
  ADD_IRQ_GATE(15);

  /* Load IDT */
  __asm__ __volatile__ ("lidt %0" : : "m" (idtr));
  /* Enable interrupts */
  __asm__ __volatile__ ("sti");
}

/* Add IRQ handler */
void add_irq_handler(uint8_t irq, void *handler) {
  irq_callbacks[irq] = handler;
}
