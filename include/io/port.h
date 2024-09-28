/* Include guard */
#ifndef _IO_PORT_H
#define _IO_PORT_H

/* Includes */
#include <core/types.h>

/* Function prototypes */
/* Read a byte from a port */
extern u8 port_inb(u16 port);
/* Read a word from a port */
extern u16 port_inw(u16 port);
/* Send a byte to a port */
extern void port_outb(u16 port, u8 val);
/* Send a word to a port */
extern void port_outw(u16 port, u16 val);

#endif /* _IO_PORT_H */
