/* Implements io/port.h */
#include <io/port.h>

/* Function implementations */
/* Read a byte from a port */
u8 port_inb(u16 port) {
  u8 val;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (val) : "Nd" (port));
  return val;
}
/* Read a word from a port */
u16 port_inw(u16 port) {
  u16 val;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (val) : "Nd" (port));
  return val;
}
/* Send a byte to a port */
void port_outb(u16 port, u8 val) {
  __asm__ __volatile__ ("outb %0, %1" : : "a" (val), "Nd" (port));
}
/* Send a word to a port */
void port_outw(u16 port, u16 val) {
  __asm__ __volatile__ ("outw %0, %1" : : "a" (val), "Nd" (port));
}
