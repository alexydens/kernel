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
typedef u8                  bool;
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
_Static_assert(sizeof(bool) == 1, "Wrong size for bool!");

/* Packed structs require a special symbol */
#ifdef __GNUC__
#  define __packed __attribute__((packed))
#else
#error "Can't use packed structs on this compiler!"
#  define __packed
#endif

/* Ensure something is aligned (e.g. aligned to page boundary) */
#ifdef __GNUC__
#define __aligned(x) __attribute__((aligned(x)))
#else
#error "Can't change alignment on this compiler!"
#define __aligned(x)
#endif

/* MACROS */

/* Return the number of elements in an array */
#define ARRLEN(x)   (sizeof(x) / sizeof(x[0]))
/* Swap two variables */
#define SWAP(x, y)  do { __typeof(x) tmp = x; x = y; y = tmp; } while (0)
/* Get maximum value */
#define MAX(x, y)   ((x) > (y) ? (x) : (y))
/* Get minimum value */
#define MIN(x, y)   ((x) < (y) ? (x) : (y))
/* Get the absolute value of a number */
#define ABS(x)      ((x) < 0 ? -(x) : (x))
/* Clamp a value between two numbers */
#define CLAMP(x, min, max)  ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/* CONSTS */

/* PI */
#define PI                 3.14159265358979323846
/* Euler's number */
#define EULER              2.71828182845904523536
/* Size prefixes */
/* One Kibibyte */
#define KiB                1024
/* One Mebibyte */
#define MiB                (1024 * 1024)
/* One Gibibyte */
#define GiB                (1024 * 1024 * 1024)
/* One Tebibyte */
#define TiB                (1024 * 1024 * 1024 * 1024)
/* Minimum and maximum for each type */
/* Max value of u8 */
#define MAX_U8             0xFF
/* Max value of u16 */
#define MAX_U16            0xFFFF
/* Max value of u32 */
#define MAX_U32            0xFFFFFFFF
/* Max value of u64 */
#define MAX_U64            0xFFFFFFFFFFFFFFFF
/* Min value of i8 */
#define MIN_I8             -128
/* Max value of i8 */
#define MAX_I8             127
/* Min value of i16 */
#define MIN_I16            -32768
/* Max value of i16 */
#define MAX_I16            32767
/* Min value of i32 */
#define MIN_I32            -2147483648
/* Max value of i32 */
#define MAX_I32            2147483647
/* Min value of i64 */
#define MIN_I64            -9223372036854775808
/* Max value of i64 */
#define MAX_I64            9223372036854775807
/* Infinity */
#define INFINITY           (1.0 / 0.0)
/* Negative infinity */
#define NEG_INFINITY       (-1.0 / 0.0)
/* NaN */
#define NAN                (0.0 / 0.0)
/* A null pointer */
#define NULL               ((void*)0)

/* LINKER SYMBOLS */

extern u32 _init_PD[1024];
extern u32 _init_PT0[1024];

/* UTILITY FUNCTIONS */

/* Memset */
static inline void *memset(void *dst, u8 val, u32 size) {
  if (!dst) return NULL;
  if (!size) return dst;
  for (u32 i = 0; i < size; i++) ((u8 *)dst)[i] = val;
  return dst;
}

/* Memcpy */
static inline void *memcpy(void *dst, const void *src, u32 size) {
  if (!dst || !src) return NULL;
  if (!size) return dst;
  for (u32 i = 0; i < size; i++) ((u8 *)dst)[i] = ((u8 *)src)[i];
  return dst;
}

/* Strlen */
static inline u32 strlen(const char *str) {
  if (!str) return 0;
  u32 len = 0;
  while (str[len]) len++;
  return len;
}

#endif /* CORE_BASE_H */
