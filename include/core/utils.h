/* Include guard */
#ifndef _UTILS_H
#define _UTILS_H

/* Some utility functions, such as the ones the stdlib would usually provide */

/* Includes */
#include <core/types.h>
#include <core/consts.h>
#include <core/macros.h>

/* Hex string from an 8 bit number */
static inline void hex_str_8(u8 num, char *str) {
  for (int i = 0; i < 2; i++) {
    str[1 - i] = HEX_CHAR((num >> (i * 4)) & 0xF);
  }
}
/* Hex string from a 16 bit number */
static inline void hex_str_16(u16 num, char *str) {
  for (int i = 0; i < 4; i++) {
    str[3 - i] = HEX_CHAR((num >> (i * 4)) & 0xF);
  }
}
/* Hex string from a 32 bit number */
static inline void hex_str_32(u32 num, char *str) {
  for (int i = 0; i < 8; i++) {
    str[7 - i] = HEX_CHAR((num >> (i * 4)) & 0xF);
  }
}
/* Hex string from a 64 bit number */
static inline void hex_str_64(u64 num, char *str) {
  for (int i = 0; i < 16; i++) {
    str[15 - i] = HEX_CHAR((num >> (i * 4)) & 0xF);
  }
}

/* Fill a buffer with a value */
static inline void memset(void *ptr, u8 value, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((u8 *)ptr)[i] = value;
  }
}
/* Copy a buffer */
static inline void memcpy(void *dst, const void *src, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((u8 *)dst)[i] = ((u8 *)src)[i];
  }
}
/* Get length of string with null terminator */
static inline size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

#endif /* _UTILS_H */
