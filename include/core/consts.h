/* Include guard */
#ifndef _CONSTS_H
#define _CONSTS_H

/* Some constants */

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

#endif /* _CONSTS_H */
