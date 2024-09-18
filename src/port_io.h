/* Include guard */
#ifndef _PORT_IO_H
#define _PORT_IO_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Read a byte from a port */
extern uint8_t portbin(uint16_t port);
/* Read a word from a port */
extern uint16_t portwin(uint16_t port);
/* Write a byte to a port */
extern void portbout(uint16_t port, uint8_t value);
/* Write a word to a port */
extern void portwout(uint16_t port, uint16_t value);

#endif /* _PORT_IO_H */
