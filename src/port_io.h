/* Include guard */
#ifndef _PORT_IO_H
#define _PORT_IO_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Read a byte from a port */
extern uint8_t _portbin(uint16_t port);
/* Read a word from a port */
extern uint16_t _portwin(uint16_t port);
/* Write a byte to a port */
extern void _portbout(uint16_t port, uint8_t value);
/* Write a word to a port */
extern void _portwout(uint16_t port, uint16_t value);

#endif /* _PORT_IO_H */
