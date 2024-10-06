/* Include guard */
#ifndef _CORE_CONF_H
#define _CORE_CONF_H

/* This contains configuration details for the entire project. */

/* Includes */
#include <core/types.h>

/* I/O SUBSYSTEMS */
/* Serial ports (COM1-COM4) */
#include <io/serial.h>
/* VGA text mode 80x25 terminal */
//#include <io/vga_term.h>
/* PS/2 keyboard interface with PIC */
//#include <io/ps2_kbd.h>
/* Timer interface with PIC */
//#include <io/timer.h>
/* ACPI interface (power on/off) */
//#include <io/acpi.h>

/* MEMORY SUBSYSTEMS */
/* Page frame allocator */
#include <mem/page_frame_alloc.h>
/* Kernel heap allocator */
//#include <mem/kalloc.h>

/* FILESYSTEM SUBSYSTEMS */

/* SYSTEM SUBSYSTEMS */
/* The IDT, ISRs, IRQs and the PIC */
#include <sys/idt.h>
/* The GDT */
#include <sys/gdt.h>
/* Any setup required for memory management with paging */
//#include <sys/paging.h>

#endif /* _CORE_CONF_H */
