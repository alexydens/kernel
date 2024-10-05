/* Include guard */
#ifndef _IO_PORT_H
#define _IO_PORT_H

/* Ported I/O interface */

/* Includes */
#include <core/types.h>

/* Read in a byte from a port */
extern u8 port_inb(u16 port);
/* Read in a word from a port */
extern u16 port_inw(u16 port);
/* Write a byte to a port */
extern void port_outb(u16 port, u8 data);
/* Write a word to a port */
extern void port_outw(u16 port, u16 data);

#endif /* _IO_PORT_H */
