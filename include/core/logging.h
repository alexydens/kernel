/* Include guard */
#ifndef _CORE_LOGGING_H
#define _CORE_LOGGING_H

/* Includes */
#include <core/types.h>
#include <io/serial.h>
#include <io/vga_term.h>

/* Macros */
#ifdef VGA_TERM_ENABLED
/* Log something to the vga text terminal and the serial port */
#define LOG(msg) do {\
  vga_term_puts(msg);\
  serial_send_str(SERIAL_COM1, msg);\
} while (0)
#else
/* Log something to the serial port */
#define LOG(msg) do {\
  vga_term_puts(msg);\
  serial_send_str(SERIAL_COM1, msg);\
} while (0)
#endif

/* Assertion in kernel */
#define ASSERT(expr) do {\
  if (!(expr)) {\
    LOG("Assertion failed: " #expr "\r\n");\
    __asm__ __volatile__ ("cli;hlt");\
    while(1);\
    __builtin_unreachable();\
  }\
} while (0)

#endif /* _CORE_LOGGING_H */
