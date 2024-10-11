/* Include guard */
#ifndef CORE_BASE_H
#define CORE_BASE_H

/* UNSIGNED INTEGERS */

/* Unsigned 8 bit integer */
typedef unsigned char       u8;
/* Unsigned 16 bit integer */
typedef unsigned short      u16;
/* Unsigned 32 bit integer */
typedef unsigned int        u32;
/* Unsigned 64 bit integer */
typedef unsigned long long  u64;

/* SIGNED INTEGERS */

/* Signed 8 bit integer */
typedef signed char         i8;
/* Signed 16 bit integer */
typedef signed short        i16;
/* Signed 32 bit integer */
typedef signed int          i32;
/* Signed 64 bit integer */
typedef signed long long    i64;

/* FLOATING POINT INTEGERS */

/* 32 bit floating point */
typedef float               f32;
/* 64 bit floating point */
typedef double              f64;

/* BOOLEANS */

/* 8 bit boolean type */
typedef u8                  b8;
enum { false, true };

/* Static assertions to guarantee sizes */
_Static_assert(sizeof(u8) == 1, "Wrong size for u8!");
_Static_assert(sizeof(u16) == 2, "Wrong size for u16!");
_Static_assert(sizeof(u32) == 4, "Wrong size for u32!");
_Static_assert(sizeof(u64) == 8, "Wrong size for u64!");
_Static_assert(sizeof(i8) == 1, "Wrong size for i8!");
_Static_assert(sizeof(i16) == 2, "Wrong size for i16!");
_Static_assert(sizeof(i32) == 4, "Wrong size for i32!");
_Static_assert(sizeof(i64) == 8, "Wrong size for i64!");
_Static_assert(sizeof(f32) == 4, "Wrong size for f32!");
_Static_assert(sizeof(f64) == 8, "Wrong size for f64!");
_Static_assert(sizeof(b8) == 1, "Wrong size for b8!");

/* Packed structs require a special symbol */
#ifdef __GNUC__
#  define __packed __attribute__((packed))
#else
#  define __packed
#endif

#endif /* CORE_BASE_H */
