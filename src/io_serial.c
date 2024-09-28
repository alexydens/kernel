/* Implements io/serial.h */
#include <io/serial.h>

/* Consts */
/* The divisor for the serial port */
#define DIVISOR 9600

/* Macros */
/* The offsets from the base ports */
/* The data port */
#define SERIAL_DATA(port)           (port)
/* The first in first out command port */
#define SERIAL_FIFO_COMMAND(port)   (port + 2)
/* The line command port */
#define SERIAL_LINE_COMMAND(port)   (port + 3)
/* The modem command port */
#define SERIAL_MODEM_COMMAND(port)  (port + 4)
/* The status port */
#define SERIAL_LINE_STATUS(port)    (port + 5)

/* Helper functions */
/* Check if transmit buffer is empty */
static inline bool serial_tx_empty(u16 port) {
  return port_inb(SERIAL_LINE_STATUS(port)) & 0x20;
}

/* Function implementations */
/* Configure a serial port for sending data to */
void serial_configure(u16 port) {
  /* Configure baud rate */
  port_outb(SERIAL_LINE_COMMAND(port), 0x80);
  port_outb(SERIAL_DATA(port), (DIVISOR >> 8) & 0xFF);
  port_outb(SERIAL_DATA(port), DIVISOR & 0xFF);
  /* Configure the line */
  port_outb(SERIAL_LINE_COMMAND(port), 0x03);
  /* Configure the buffers */
  port_outb(SERIAL_FIFO_COMMAND(port), 0xC7);
  /* Configure the modem */
  port_outb(SERIAL_MODEM_COMMAND(port), 0x03);
}
/* Send a buffer to a serial port */
void serial_send_buf(u16 port, buf_t buffer) {
  u16 i;
  for (i = 0; i < buffer.size; i++) {
    while (!serial_tx_empty(port));
    port_outb(SERIAL_DATA(port), ((u8 *)buffer.ptr)[i]);
  }
}
/* Send a null terminated string to a serial port */
void serial_send_str(u16 port, char *str) {
  while (*str) {
    while (!serial_tx_empty(port));
    port_outb(SERIAL_DATA(port), *str);
    str++;
  }
}
/* Send a single character to a serial port */
void serial_send_char(u16 port, char c) {
  while (!serial_tx_empty(port));
  port_outb(SERIAL_DATA(port), c);
}
