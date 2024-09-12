/* Implements idt.h */
#include "idt.h"

/* Macros */
#define ADD_IDT_GATE(num) idt_set_gate(num, (uint32_t)isr_##num, 0x08, 0x8E)

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
  0,
  "x87 floating point exception",
  "Alignment check",
  "Machine check",
  "SIMD floating point exception",
  "Virtualization exception",
  "Control protection exception",
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Globals */
struct idtr idtr;
struct idt_entry entries[256];

/* Generic isr handler */
struct isr_args {
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags;
  uint32_t esp, ss;
};
void isr_handler_common(struct isr_args args) {
  graphics_vga_puts("Interrupt: ");
  graphics_vga_puts(iterrupt_names[args.interrupt_number]);
  graphics_vga_puts("\r\n");
  __asm__ __volatile__ ("cli");
  __asm__ __volatile__ ("hlt");
}

/* First 22 ISRs */
extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);
extern void isr_21(void);
extern void isr_22(void);
extern void isr_23(void);
extern void isr_24(void);
extern void isr_25(void);
extern void isr_26(void);
extern void isr_27(void);
extern void isr_28(void);
extern void isr_29(void);
extern void isr_30(void);
extern void isr_31(void);

static inline void idt_set_gate(
    uint8_t index,
    uint32_t handler,
    uint16_t segment,
    uint8_t flags
) {
  entries[index].isr_0_15 = handler & 0xFFFF;
  entries[index].isr_16_31 = (handler >> 16) & 0xFFFF;
  entries[index].segment = segment;
  entries[index].reserved = 0;
  entries[index].flags = flags;
}

/* IDT Initialization */
void idt_init(void) {
  idtr.limit = sizeof(struct idt_entry) * 256 - 1;
  idtr.base = (uint32_t)&entries;

  memset(entries, 0, sizeof(struct idt_entry) * 256);

  ADD_IDT_GATE(0);
  ADD_IDT_GATE(1);
  ADD_IDT_GATE(2);
  ADD_IDT_GATE(3);
  ADD_IDT_GATE(4);
  ADD_IDT_GATE(5);
  ADD_IDT_GATE(6);
  ADD_IDT_GATE(7);
  ADD_IDT_GATE(8);
  ADD_IDT_GATE(9);
  ADD_IDT_GATE(10);
  ADD_IDT_GATE(11);
  ADD_IDT_GATE(12);
  ADD_IDT_GATE(13);
  ADD_IDT_GATE(14);
  ADD_IDT_GATE(15);
  ADD_IDT_GATE(16);
  ADD_IDT_GATE(17);
  ADD_IDT_GATE(18);
  ADD_IDT_GATE(19);
  ADD_IDT_GATE(20);
  ADD_IDT_GATE(21);
  ADD_IDT_GATE(22);
  ADD_IDT_GATE(23);
  ADD_IDT_GATE(24);
  ADD_IDT_GATE(25);
  ADD_IDT_GATE(26);
  ADD_IDT_GATE(27);
  ADD_IDT_GATE(28);
  ADD_IDT_GATE(29);
  ADD_IDT_GATE(30);
  ADD_IDT_GATE(31);

  __asm__ __volatile__ ("lidt %0" : : "m" (idtr));
  __asm__ __volatile__ ("sti");
}
