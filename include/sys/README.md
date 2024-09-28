# System Directory
The system directory contains all the other important headers. This includes
things like code to handle interrupts, descriptor tables, and scheduling.
Examples include:
- The GDT interface, stored in `sys/gdt.h`.
- The IDT interface, stored in `sys/idt.h`.
- The TSS interface, stored in `sys/tss.h`.
- The code to setup paging, stored in `sys/paging.h`.
