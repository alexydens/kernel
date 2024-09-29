/* Include guard */
#ifndef _CORE_LOGGING_H
#define _CORE_LOGGING_H

/* Includes */
#include <core/types.h>
#include <io/port.h>
#include <io/vga_term.h>

/* Macros */
/* Log something to the vga text terminal and the serial port */
#define LOG(msg) do {\
  vga_term_puts(msg);\
  serial_send_str(SERIAL_COM1, msg);\
} while (0)

#endif /* _CORE_LOGGING_H */
