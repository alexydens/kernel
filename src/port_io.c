/* Implements port_io.h */
#include "port_io.h"

/* Read a byte from a port */
uint8_t portbin(uint16_t port) {
  uint8_t value;
  __asm__ volatile ("in %%dx, %%al" : "=a" (value) : "d" (port));
  return value;
}
/* Read a word from a port */
uint16_t portwin(uint16_t port) {
  uint16_t value;
  __asm__ volatile ("in %%dx, %%ax" : "=a" (value) : "d" (port));
  return value;
}

/* Write a byte to a port */
void portbout(uint16_t port, uint8_t value) {
  __asm__ volatile ("out %%al, %%dx" : : "a" (value), "d" (port));
}
/* Write a word to a port */
void portwout(uint16_t port, uint16_t value) {
  __asm__ volatile ("out %%ax, %%dx" : : "a" (value), "d" (port));
}
