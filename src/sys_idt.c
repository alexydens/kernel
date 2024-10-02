/* Implements sys/idt.h */
#include <sys/idt.h>

/* Macros */
#define ADD_ISR_GATE(num) idt_set_gate(\
    num,\
    (u32)_isr_##num,\
    SEG_SELECTOR_KERNELCODE,\
    IDT_FLAGS_PRESENT | IDT_FLAGS_RING0 | IDT_FLAGS_TYPE_IG32)
#define ADD_IRQ_GATE(num) idt_set_gate(\
    num+32,\
    (u32)_irq_##num,\
    SEG_SELECTOR_KERNELCODE,\
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

/* Generic isr handler */
struct isr_args {
  u32 interrupt_number, error_code;
  u32 eip, cs, eflags;
  u32 esp, ss;
};
void isr_handler_common(struct isr_args *args) {
  /* Variables */
  u32 page_fault_addr;
  char addr_str[9];
  /* Print the interrupt name */
  LOG("Interrupt: ");
  LOG(iterrupt_names[args->interrupt_number]);
  LOG("\r\n");
  switch (args->interrupt_number) {
    case 14: /* Page fault */
      /* Error code */
      /* User/supervisor */
      if (args->error_code & 0x4) LOG("User ");
      else LOG("Supervisor ");
      /* Read/write */
      if (args->error_code & 0x2) LOG("tried to read ");
      else LOG("tried to write ");
      /* Present */
      if (args->error_code & 0x1) LOG("a present page\r\n");
      else LOG("a non-present page\r\n");
      /* Print the faulting address */
      LOG("Address was: 0x");
      __asm__ __volatile__ ("mov %%cr2, %0" : "=r" (page_fault_addr));
      hex_str_32(page_fault_addr, addr_str);
      LOG(addr_str);
      LOG("\r\n");
      LOG("Halting...\r\n");
      __asm__ __volatile__ ("cli;hlt");

      break;
    default:
      break;
  }
}
/* Generic irq handler */
void irq_handler_common(irq_args_t *args) {
  /* Print the irq number */
  /*LOG("IRQ: ");
  char str[3];
  str[0] = '0' + (args->irq_number / 10);
  str[1] = '0' + (args->irq_number % 10);
  str[2] = '\0';
  LOG(str);
  LOG("\r\n");*/

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
    u8 index,
    u32 handler,
    u16 segment,
    u8 flags) {
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
  idtr.base = (u32)&entries;

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
void add_irq_handler(u8 irq, irq_handler_t handler) {
  irq_callbacks[irq] = handler;
}
