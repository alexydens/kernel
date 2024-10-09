/* Include guard */
#ifndef _CORE_UTILS_H
#define _CORE_UTILS_H

/* Some utility functions, such as the ones the stdlib would usually provide */

/* Includes */
#include <core/types.h>
#include <core/consts.h>
#include <core/macros.h>
#include <stdarg.h>

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

/*
 * Print formatted output:
 * - '%c' - print a character.
 * - '%s' - print a string.
 * - '%ub' - print an unsigned 8 bit integer.
 * - '%us' - print an unsigned 16 bit integer.
 * - '%ud' - print an unsigned 32 bit integer.
 * - '%ul' - print an unsigned 64 bit integer.
 * - '%xb' - print an unsigned 8 bit integer as hex.
 * - '%xs' - print an unsigned 16 bit integer as hex.
 * - '%xd' - print an unsigned 32 bit integer as hex.
 * - '%xl' - print an unsigned 64 bit integer as hex.
 * - '%ib' - print a signed 8 bit integer.
 * - '%is' - print a signed 16 bit integer.
 * - '%id' - print a signed 32 bit integer.
 * - '%il' - print a signed 64 bit integer.
 * - '%b' - print a boolean as 'true' or 'false'.
 * - '%bb' - print a boolean as '0' or '1'.
 */
static inline void kprintf(void (*kputc)(char), const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *arg_string;
  char ntostr[21];

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'u':
          switch (format[1]) {
            case 'b':
              format++;
              u8_decstr(va_arg(args, unsigned), ntostr);
              for (int i = 0; i < 3; i++) {
                if (ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
            case 's':
              format++;
              u16_decstr(va_arg(args, unsigned), ntostr);
              for (int i = 0; i < 5; i++) {
                if (ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
            case 'd':
              format++;
              u32_decstr(va_arg(args, u32), ntostr);
              for (int i = 0; i < 10; i++) {
                if (ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
#ifdef U64_DIV_ALLOWED
            case 'l':
              format++;
              u64_decstr(va_arg(args, u64), ntostr);
              for (int i = 0; i < 20; i++) {
                if (ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
#endif
            default:
              break;
          }
          break;
        case 'i':
          switch (format[1]) {
            case 'b':
              format++;
              i8_decstr(va_arg(args, int), ntostr);
              for (int i = 0; i < 4; i++) {
                if (ntostr[i] == ' ' || ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
            case 's':
              format++;
              i16_decstr(va_arg(args, int), ntostr);
              for (int i = 0; i < 6; i++) {
                if (ntostr[i] == ' ' || ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
            case 'd':
              format++;
              i32_decstr(va_arg(args, i32), ntostr);
              for (int i = 0; i < 11; i++) {
                if (ntostr[i] == ' ' || ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
#ifdef I64_DIV_ALLOWED
            case 'l':
              format++;
              i64_decstr(va_arg(args, i64), ntostr);
              for (int i = 0; i < 21; i++) {
                if (ntostr[i] == ' ' || ntostr[i] == '0') continue;
                kputc(ntostr[i]);
              }
              break;
#endif
            default:
              break;
          }
          break;
        case 'x':
          switch (format[1]) {
            case 'b':
              format++;
              u8_hexstr(va_arg(args, unsigned), ntostr);
              for (int i = 0; i < 2; i++) {
                kputc(ntostr[i]);
              }
              break;
            case 's':
              format++;
              u16_hexstr(va_arg(args, unsigned), ntostr);
              for (int i = 0; i < 4; i++) {
                kputc(ntostr[i]);
              }
              break;
            case 'd':
              format++;
              u32_hexstr(va_arg(args, u32), ntostr);
              for (int i = 0; i < 8; i++) {
                kputc(ntostr[i]);
              }
              break;
#ifdef U64_DIV_ALLOWED
            case 'l':
              format++;
              u64_hexstr(va_arg(args, u64), ntostr);
              for (int i = 0; i < 16; i++) {
                kputc(ntostr[i]);
              }
              break;
#endif
            default:
              break;
          }
          break;
        case 'b':
          switch (format[1]) {
            case 'b':
              format++;
              kputc(va_arg(args, int) ? '1' : '0');
              break;
            default:
              if (va_arg(args, int)) {
                kputc('t');kputc('r');kputc('u');kputc('e');
              } else {
                kputc('f');kputc('a');kputc('l');kputc('s');kputc('e');
              }
              break;
          }
          break;
        case 'c':
          kputc(va_arg(args, int));
          break;
        case 's':
          arg_string = va_arg(args, char *);
          while (*arg_string != '\0') {
            kputc(*arg_string);
            arg_string++;
          }
          break;
        default:
          break;
      }
    } else {
      kputc(*format);
    }
    format++;
  }

  va_end(args);
}

#endif /* _CORE_UTILS_H */
