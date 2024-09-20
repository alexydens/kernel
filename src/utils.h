/* Include guard */
#ifndef _UTILS_H
#define _UTILS_H

/* Includes */
#include <stdint.h>
#include <stddef.h>

/* Blindly copies memory from src to dest of size bytes */
static inline void _memcpy(void *dest, void *src, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
  }
}
/* Blindly sets memory to val for size bytes of dest */
static inline void _memset(void *dest, uint8_t val, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((uint8_t *)dest)[i] = val;
  }
}
/* Gets the length of a null terminated string */
static inline size_t _strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

#endif /* _UTILS_H */
