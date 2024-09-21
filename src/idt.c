/* Implements idt.h */
#include "idt.h"

/* Macros */
#define ADD_IDT_GATE(num) idt_set_gate(\
    num,\
    (uint32_t)_isr_##num,\
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
static idtr_t idtr;
static idt_entry_t entries[256];

#include "vga_text_term.h"
/* Generic isr handler */
struct isr_args {
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags;
  uint32_t esp, ss;
};
__attribute__((noreturn)) void isr_handler_common(struct isr_args args) {
  vga_text_puts("Interrupt: ");
  vga_text_puts(iterrupt_names[args.interrupt_number]);
  vga_text_puts("\r\n");
  __asm__ __volatile__ ("cli");
  __asm__ __volatile__ ("hlt");
  __builtin_unreachable();
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

  /* Load IDT */
  __asm__ __volatile__ ("lidt %0" : : "m" (idtr));
  /* Enable interrupts */
  __asm__ __volatile__ ("sti");
}
