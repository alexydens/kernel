/* Include guard */
#if !defined(UTILS_H)
#define UTILS_H

/* Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* The end of the kernel - address of var is important, not value */
extern int end_kernel;
#define KERNEL_END ((void*)(&end_kernel))

/* Blindly copies memory from src to dest of size bytes */
static inline void memcpy(void *dest, void *src, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
  }
}
/* Blindly sets memory to val for size bytes of dest */
static inline void memset(void *dest, uint8_t val, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((uint8_t *)dest)[i] = val;
  }
}

/* Gets the length of a NUL-terminated string */
static inline size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

#endif /* UTILS_H */
