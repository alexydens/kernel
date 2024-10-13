/* Include guard */
#ifndef IO_PORT_H
#define IO_PORT_H

/* Includes */
#include <core/base.h>

/* Read a byte from a port */
static inline u8 port_inb(u16 port) {
  u8 value;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (value) : "Nd" (port));
  return value;
}
/* Read a word from a port */
static inline u16 port_inw(u16 port) {
  u16 value;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (value) : "Nd" (port));
  return value;
}

/* Write a byte to a port */
static inline void port_outb(u16 port, u8 value) {
  __asm__ __volatile__ ("outb %0, %1" : : "a" (value), "Nd" (port));
}
/* Write a word to a port */
static inline void port_outw(u16 port, u16 value) {
  __asm__ __volatile__ ("outw %0, %1" : : "a" (value), "Nd" (port));
}

#endif /* IO_PORT_H */
