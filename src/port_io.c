/* Implements port_io.h */
#include "port_io.h"

/* Read a byte from a port */
uint8_t port_in_byte(uint16_t port) {
  uint8_t value;
  __asm__ volatile ("in %%dx, %%al" : "=a" (value) : "d" (port));
  return value;
}
/* Read a word from a port */
uint16_t port_in_word(uint16_t port) {
  uint16_t value;
  __asm__ volatile ("in %%dx, %%ax" : "=a" (value) : "d" (port));
  return value;
}

/* Write a byte to a port */
void port_out_byte(uint16_t port, uint8_t value) {
  __asm__ volatile ("out %%al, %%dx" : : "a" (value), "d" (port));
}
/* Write a word to a port */
void port_out_word(uint16_t port, uint16_t value) {
  __asm__ volatile ("out %%ax, %%dx" : : "a" (value), "d" (port));
}
