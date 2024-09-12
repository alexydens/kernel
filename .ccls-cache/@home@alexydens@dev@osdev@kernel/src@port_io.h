/* Include guard */
#if !defined(PORT_IO_H)
#define PORT_IO_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Read a byte from a port */
extern uint8_t port_in_byte(uint16_t port);
/* Read a word from a port */
extern uint16_t port_in_word(uint16_t port);
/* Write a byte to a port */
extern void port_out_byte(uint16_t port, uint8_t value);
/* Write a word to a port */
extern void port_out_word(uint16_t port, uint16_t value);

#endif /* PORT_IO_H */
