/* Include guard */
#ifndef CORE_PUTTYPES_H
#define CORE_PUTTYPES_H

/* Includes */
#include <core/base.h>

/* Print a u8 to the screen in hex */
static inline void put8hex(u8 val, void (*putc)(u8)) {
  const char *hex = "0123456789abcdef";
  putc(hex[(val >> 4) & 0xF]);
  putc(hex[val & 0xF]);
}
/* Print a u16 to the screen in hex */
static inline void put16hex(u16 val, void (*putc)(u8)) {
  put8hex(val >> 8, putc);
  put8hex(val, putc);
}
/* Print a u32 to the screen in hex */
static inline void put32hex(u32 val, void (*putc)(u8)) {
  put16hex(val >> 16, putc);
  put16hex(val, putc);
}
/* Print a u64 to the screen in hex */
static inline void put64hex(u64 val, void (*putc)(u8)) {
  put32hex(val >> 32, putc);
  put32hex(val, putc);
}

#endif /* CORE_PUTTYPES_H */
