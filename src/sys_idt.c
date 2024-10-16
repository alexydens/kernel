/* Implements sys/idt.h */
#include <sys/idt.h>

/* Consts */
/* IDT flags */
#define IDT_FLAGS_PRESENT     (1 << 7) /* Is this entry present? */
#define IDT_FLAGS_RING0       (0 << 5) /* DPL = 0 */
#define IDT_FLAGS_RING1       (1 << 5) /* DPL = 1 */
#define IDT_FLAGS_RING2       (2 << 5) /* DPL = 2 */
#define IDT_FLAGS_RING3       (3 << 5) /* DPL = 3 */
#define IDT_GATETYPE_TASK     (0x5)    /* Task gate */
#define IDT_GATETYPE_INT16    (0x6)    /* 16-bit interrupt gate */
#define IDT_GATETYPE_TRAP16   (0x7)    /* 16-bit trap gate */
#define IDT_GATETYPE_INT32    (0xE)    /* 32-bit interrupt gate */
#define IDT_GATETYPE_TRAP32   (0xF)    /* 32-bit trap gate */
/* The names of all the exceptions */
char *exception_names[] = {
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

/* The IDT entry structure */
struct __packed idt_entry {
  u16 offset_low;
  u16 selector;
  u8 reserved;
  u8 flags;
  u16 offset_high;
};

/* The IDT Descriptor structure */
struct __packed idtr {
  u16 limit;
  u32 base;
};

/* Global variables */
static struct idtr idtr __aligned(0x10);
static struct idt_entry idt[256] __aligned(0x10);

/* Utility functions */
static inline void set_kernel_entry(
    u32 index,
    u32 offset,
    u8 flags
) {
  idt[index].offset_low = offset & 0xFFFF;
  idt[index].offset_high = (offset >> 16) & 0xFFFF;
  idt[index].selector = GDT_SEGMENT_KERNELCODE;
  idt[index].reserved = 0;
  idt[index].flags = flags;
}
static inline void set_user_entry(
    u32 index,
    u32 offset,
    u8 flags
) {
  idt[index].offset_low = offset & 0xFFFF;
  idt[index].offset_high = (offset >> 16) & 0xFFFF;
  idt[index].selector = GDT_SEGMENT_USERCODE;
  idt[index].reserved = 0;
  idt[index].flags = flags;
}
/* Macros for utils */
#define ADD_ISR_GATE(num) set_kernel_entry(\
    num,\
    (u32)_isr_##num,\
    IDT_FLAGS_PRESENT\
    | IDT_FLAGS_RING0\
    | IDT_GATETYPE_INT32)

/* All the routines... */
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

/* The common exception handler */
void isr_handler_common(struct isr_args *args) {
  /* Print exception type */
  serial_printf(
      "Exception: %s\r\n",
      exception_names[args->interrupt_number]
  );
  /* Check for certain exceptions, handle them */
  switch (args->interrupt_number) {
    case 14: /* Page fault */
      {
        u32 addr;
        __asm__ __volatile__ ("mov %%cr2,%0" : "=r" (addr));
        serial_printf(
            "Address was: 0x%08x\r\n"
            "%s process tried to %s a %s page.\r\n",
            addr,
            args->error_code & 0x4 ? "User" : "Supervisor",
            args->error_code & 0x2 ? "read" : "write",
            args->error_code & 0x1 ? "present" : "non-present"
        );
      }
      break;
    default:
      break;
  }
  /* Halt */
  serial_printf("Halting...\r\n");
  __asm__ __volatile__ ("cli;hlt");
}

/* Initialize the IDT */
bool idt_init(void) {
  /* Set all entries to 0 */
  memset(idt, 0, sizeof(idt));

  /* Add all the exception gates */
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

  /* Set the IDT limit */
  idtr.limit = sizeof(idt) - 1;
  /* Set the IDT base */
  idtr.base = (u32)&idt;

  /* Load IDT */
  __asm__ __volatile__ ("lidt %0" : : "m" (idtr));

  /* Enable interrupts */
  __asm__ __volatile__ ("sti");

  /* Long jump (for some reason) */
  __asm__ __volatile__ ("ljmp $0x08, $1f");
  __asm__ __volatile__ ("1:");

  /* Disable PIC */
  port_outb(0x21, 0xff);
  port_outb(0xa1, 0xff);

  return true;
}
