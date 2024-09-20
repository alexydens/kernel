/* Implements port_io.h */
#include "port_io.h"

/* Read a byte from a port */
uint8_t _portbin(uint16_t port) {
  uint8_t value;
  __asm__ volatile ("in %%dx, %%al" : "=a" (value) : "d" (port));
  return value;
}
/* Read a word from a port */
uint16_t _portwin(uint16_t port) {
  uint16_t value;
  __asm__ volatile ("in %%dx, %%ax" : "=a" (value) : "d" (port));
  return value;
}

/* Write a byte to a port */
void _portbout(uint16_t port, uint8_t value) {
  __asm__ volatile ("out %%al, %%dx" : : "a" (value), "d" (port));
}
/* Write a word to a port */
void _portwout(uint16_t port, uint16_t value) {
  __asm__ volatile ("out %%ax, %%dx" : : "a" (value), "d" (port));
}
