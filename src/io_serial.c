/* Implement io/serial.h */
#include <io/serial.h>

/* The different offsets for the serial ports */
/* Serial data */
#define SERIAL_DATA_PORT(base)          (base)
/* Command first in first out */
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
/* Line command */
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
/* Modem command */
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
/* Line status */
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* Commands */
/* Enable DLAB - allow the divisor to come byte by byte */
#define SERIAL_LINE_ENABLE_DLAB         0x80

/* Global state */
static bool initialized = false;

/* Setup a serial port */
static void _setup_com(u16 port) {
  /* Configure line */
  port_outb(SERIAL_LINE_COMMAND_PORT(port), 0x00);
  /* Configure buffers */
  port_outb(SERIAL_FIFO_COMMAND_PORT(port), 0xC7);
  /* Configure modem */
  port_outb(SERIAL_MODEM_COMMAND_PORT(port), 0x0B);
}

/* Initialize all serial ports (return false on error) */
bool serial_init(void) {
  serial_set_divisor(1, SERIAL_PORT_COM1);
  serial_set_divisor(1, SERIAL_PORT_COM2);
  serial_set_divisor(1, SERIAL_PORT_COM3);
  serial_set_divisor(1, SERIAL_PORT_COM4);
  _setup_com(SERIAL_PORT_COM1);
  _setup_com(SERIAL_PORT_COM2);
  _setup_com(SERIAL_PORT_COM3);
  _setup_com(SERIAL_PORT_COM4);
  initialized = true;
  return true;
}
/* Have the serial ports been initialized? */
bool serial_initialized(void) {
  return initialized;
}

/* Send a character to a serial port */
void serial_putc(char c, u16 port) {
  if (!initialized) return;
  while ((port_inb(SERIAL_LINE_STATUS_PORT(port)) & 0x20) == 0);
  port_outb(SERIAL_DATA_PORT(port), c);
}
/* Send a string to a serial port */
void serial_puts(const char *str, u16 port) {
  if (!initialized) return;
  while (*str) {
    serial_putc(*str, port);
    str++;
  }
}
/* Change the divisor for a serial port */
void serial_set_divisor(u16 divisor, u16 port) {
  port_outb(SERIAL_LINE_COMMAND_PORT(port), SERIAL_LINE_ENABLE_DLAB);
  port_outb(SERIAL_DATA_PORT(port), (divisor >> 8) & 0xff);
  port_outb(SERIAL_DATA_PORT(port), (divisor) & 0xff);
}

/* Putc for serial printf */
void _serial_putc(char c) {
  serial_putc(c, SERIAL_PORT_COM1);
}
