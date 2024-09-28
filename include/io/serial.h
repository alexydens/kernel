/* Include guard */
#ifndef _IO_SERIAL_H
#define _IO_SERIAL_H

/* Includes */
#include <core/types.h>
#include <io/port.h>

/* Consts */
/* The serial ports */
/* Serial port - COM1 */
#define SERIAL_COM1          0x3F8
/* Serial port - COM2 */
#define SERIAL_COM2          0x2F8
/* Serial port - COM3 */
#define SERIAL_COM3          0x3E8
/* Serial port - COM4 */
#define SERIAL_COM4          0x2E8
/* Serial port - COM5 */
#define SERIAL_COM5          0x5F8
/* Serial port - COM6 */
#define SERIAL_COM6          0x4F8
/* Serial port - COM7 */
#define SERIAL_COM7          0x5E8
/* Serial port - COM8 */
#define SERIAL_COM8          0x4E8

/* Function prototypes */
/* Configure a serial port for sending data to */
extern void serial_configure(u16 port);
/* Send a buffer to a serial port */
extern void serial_send_buf(u16 port, buf_t buffer);
/* Send a null terminated string to a serial port */
extern void serial_send_str(u16 port, char *str);
/* Send a single character to a serial port */
extern void serial_send_char(u16 port, char c);

#endif /* _IO_SERIAL_H */
