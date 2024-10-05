/* Include guard */
#ifndef _CORE_UTILS_H
#define _CORE_UTILS_H

/* Some utility functions, such as the ones the stdlib would usually provide */

/* Includes */
#include <core/types.h>
#include <core/consts.h>
#include <core/macros.h>

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

#endif /* _CORE_UTILS_H */
