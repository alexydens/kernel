/* Include guard */
#ifndef _TYPES_H
#define _TYPES_H

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
  void *ptr;
  size_t size;
} buf_t;

#endif /* _TYPES_H */
