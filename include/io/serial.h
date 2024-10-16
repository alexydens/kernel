/* Include guard */
#ifndef IO_SERIAL_H
#define IO_SERIAL_H

/* Includes */
#include <core/base.h>
#include <core/printf.h>
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
extern bool serial_init(u16 divisor);

/* Send a character to a serial port */
extern void serial_putc(char c, u16 port);
/* Send a string to a serial port */
extern void serial_puts(const char *str, u16 port);
/* Change the divisor for a serial port */
extern void serial_set_divisor(u16 divisor, u16 port);

/* Put a character to com1 (internal, just for macro) */
static inline void _putc_com1(char c) { serial_putc(c, SERIAL_PORT_COM1); }
/* Printf to com1 */
#define serial_printf(...) _printf(_putc_com1, __VA_ARGS__)

#endif /* IO_SERIAL_H */
