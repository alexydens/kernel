/* Include guard */
#ifndef _CORE_TYPES_H
#define _CORE_TYPES_H

/*
 * This contains some base types for the operating system, as well as some more
 * structured ones. It relies on the presence of stdint.h, stddef.h and
 * stdbool.h.
 */

/* Includes */
#include <stdint.h>   /* uint8_t, uint16_t, uint32_t, etc. */
#include <stddef.h>   /* size_t, NULL */
#include <stdbool.h>  /* bool */

/* Unsigned integers */
/* Unsigned 8 bit integer */
typedef uint8_t   u8;
/* Unsigned 16 bit integer */
typedef uint16_t  u16;
/* Unsigned 32 bit integer */
typedef uint32_t  u32;
/* Unsigned 64 bit integer */
typedef uint64_t  u64;

/* Signed integers */
/* Signed 8 bit integer */
typedef int8_t    i8;
/* Signed 16 bit integer */
typedef int16_t   i16;
/* Signed 32 bit integer */
typedef int32_t   i32;
/* Signed 64 bit integer */
typedef int64_t   i64;

/* Floating point numbers */
/* 32 bit floating point number */
typedef float     f32;
/* 64 bit floating point number */
typedef double    f64;

/* A void function pointer */
typedef void (*fn_ptr_t)(void);

/* A buffer */
typedef struct {
  void *data;
  size_t size;
} buf_t;

/* A string */
typedef struct {
  char *str;
  size_t len;
} str_t;

/* Hex char from number */
#define HEX_CHAR(x)            ((x) < 10 ? '0' + (x) : 'A' + (x) - 10)
/* Decimal char from number */
#define DEC_CHAR(x)            ((x) + '0')

/* Convert from a boolean to a string */
inline const char *bool_str(bool val) {
  return val ? "true" : "false";
}
/* Convert a u8 to a hex string */
inline void u8_hexstr(u8 val, char *str) {
  for (int i = 0; i < 2; i++) {
    str[1 - i] = HEX_CHAR((val >> (i * 4)) & 0xF);
  }
}
/* Convert a u8 to a decimal string (3 digits) */
inline void u8_decstr(u8 val, char *str) {
  str[2] = DEC_CHAR((val % 10));
  str[1] = DEC_CHAR((val / 10) % 10);
  str[0] = DEC_CHAR((val / 100) % 10);
}
/* Convert a u16 to a hex string */
inline void u16_hexstr(u16 val, char *str) {
  for (int i = 0; i < 4; i++) {
    str[3 - i] = HEX_CHAR((val >> (i * 4)) & 0xF);
  }
}
/* Convert a u16 to a decimal string (5 digits) */
inline void u16_decstr(u16 val, char *str) {
  str[4] = DEC_CHAR((val % 10));
  str[3] = DEC_CHAR((val / 10) % 10);
  str[2] = DEC_CHAR((val / 100) % 10);
  str[1] = DEC_CHAR((val / 1000) % 10);
  str[0] = DEC_CHAR((val / 10000) % 10);
}
/* Convert a u32 to a hex string */
inline void u32_hexstr(u32 val, char *str) {
  for (int i = 0; i < 8; i++) {
    str[7 - i] = HEX_CHAR((val >> (i * 4)) & 0xF);
  }
}
/* Convert a u32 to a decimal string (10 digits) */
inline void u32_decstr(u32 val, char *str) {
  str[9] = DEC_CHAR((val % 10));
  str[8] = DEC_CHAR((val / 10) % 10);
  str[7] = DEC_CHAR((val / 100) % 10);
  str[6] = DEC_CHAR((val / 1000) % 10);
  str[5] = DEC_CHAR((val / 10000) % 10);
  str[4] = DEC_CHAR((val / 100000) % 10);
  str[3] = DEC_CHAR((val / 1000000) % 10);
  str[2] = DEC_CHAR((val / 10000000) % 10);
  str[1] = DEC_CHAR((val / 100000000) % 10);
  str[0] = DEC_CHAR((val / 1000000000) % 10);
}
/* Convert a u64 to a hex string */
inline void u64_hexstr(u64 val, char *str) {
  for (int i = 0; i < 16; i++) {
    str[15 - i] = HEX_CHAR((val >> (i * 4)) & 0xF);
  }
}
/* Convert a u64 to a decimal string (20 digits) */
inline void u64_decstr(u64 val, char *str) {
  str[19] = DEC_CHAR((val % 10));
  str[18] = DEC_CHAR((val / 10) % 10);
  str[17] = DEC_CHAR((val / 100) % 10);
  str[16] = DEC_CHAR((val / 1000) % 10);
  str[15] = DEC_CHAR((val / 10000) % 10);
  str[14] = DEC_CHAR((val / 100000) % 10);
  str[13] = DEC_CHAR((val / 1000000) % 10);
  str[12] = DEC_CHAR((val / 10000000) % 10);
  str[11] = DEC_CHAR((val / 100000000) % 10);
  str[10] = DEC_CHAR((val / 1000000000) % 10);
  str[9] =  DEC_CHAR((val / 10000000000) % 10);
  str[8] =  DEC_CHAR((val / 100000000000) % 10);
  str[7] =  DEC_CHAR((val / 1000000000000) % 10);
  str[6] =  DEC_CHAR((val / 10000000000000) % 10);
  str[5] =  DEC_CHAR((val / 100000000000000) % 10);
  str[4] =  DEC_CHAR((val / 1000000000000000) % 10);
  str[3] =  DEC_CHAR((val / 10000000000000000) % 10);
  str[2] =  DEC_CHAR((val / 100000000000000000) % 10);
  str[1] =  DEC_CHAR((val / 1000000000000000000) % 10);
  str[0] =  DEC_CHAR((val / 10000000000000000000u) % 10);
}
/* Convert an i8 to a decimal string (3 digits + sign) */
inline void i8_decstr(i8 val, char *str) {
  if (val < 0) {
    str[0] = '-';
    val = -val;
  }
  u8_decstr(val, str + 1);
}
/* Convert an i16 to a decimal string (5 digits + sign) */
inline void i16_decstr(i16 val, char *str) {
  if (val < 0) {
    str[0] = '-';
    val = -val;
  }
  u16_decstr(val, str + 1);
}
/* Convert an i32 to a decimal string (10 digits + sign) */
inline void i32_decstr(i32 val, char *str) {
  if (val < 0) {
    str[0] = '-';
    val = -val;
  }
  u32_decstr(val, str + 1);
}
/* Convert an i64 to a decimal string (20 digits + sign) */
inline void i64_decstr(i64 val, char *str) {
  if (val < 0) {
    str[0] = '-';
    val = -val;
  }
  u64_decstr(val, str + 1);
}

#endif /* _CORE_TYPES_H */
