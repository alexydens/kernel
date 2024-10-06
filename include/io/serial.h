/* Include guard */
#ifndef _IO_SERIAL_H
#define _IO_SERIAL_H

/* Includes */
#include <core/types.h>
#include <core/utils.h>
#include <io/port.h>

/* Serial ports (COM1-COM4) */
/* COM1 port */
#define SERIAL_PORT_COM1       0x3F8
/* COM2 port */
#define SERIAL_PORT_COM2       0x2F8
/* COM3 port */
#define SERIAL_PORT_COM3       0x3E8
/* COM4 port */
#define SERIAL_PORT_COM4       0x2E8

/* Baud rate */
/* The default baud rate */
#define SERIAL_DEFAULT_BAUD    115200
/* The default baud divisor */
#define SERIAL_DEFAULT_DIVISOR 2

/* Initialize all serial ports (return false on error) */
extern bool serial_init(void);
/* Have the serial ports been initialized? */
extern bool serial_initialized(void);

/* Send a character to a serial port */
extern void serial_putc(char c, u16 port);
/* Send a string to a serial port */
extern void serial_puts(const char *str, u16 port);
/* Change the divisor for a serial port */
extern void serial_set_divisor(u16 divisor, u16 port);

/* Putc for serial printf */
extern void _serial_putc(char c);

/* Print formatted to serial com1 */
#define serial_printf(...) kprintf(_serial_putc, __VA_ARGS__)

#endif /* _IO_SERIAL_H */
