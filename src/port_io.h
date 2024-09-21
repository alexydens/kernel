/* Include guard */
#ifndef _PORT_IO_H
#define _PORT_IO_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Read a byte from a port */
extern uint8_t port_inb(uint16_t port);
/* Read a word from a port */
extern uint16_t port_inw(uint16_t port);
/* Write a byte to a port */
extern void port_outb(uint16_t port, uint8_t value);
/* Write a word to a port */
extern void port_outw(uint16_t port, uint16_t value);

#endif /* _PORT_IO_H */
