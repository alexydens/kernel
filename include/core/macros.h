/* Include guard */
#ifndef _CORE_MACROS_H
#define _CORE_MACROS_H

/* This contains some utility macros */

/* Macro to return the number of elements in an array */
#define ARRAY_SIZE(array)      (sizeof(array) / sizeof(array[0]))

/* Macro to return the maximum of two numbers */
#define MAX(x, y)              (((x) > (y)) ? (x) : (y))
/* Macro to return the minimum of two numbers */
#define MIN(x, y)              (((x) < (y)) ? (x) : (y))
/* Get the sign of a number */
#define SIGN(x)                (((x) < 0) ? -1 : 1)
/* Get the absolute value of a number */
#define ABS(x)                 (((x) < 0) ? -(x) : (x))
/* Clamp a value between two numbers */
#define CLAMP(x, min, max)     (((x) < (min))\
    ? (min)\
    : (((x) > (max)) ? (max) : (x)))
/* Linear interpolation */
#define LERP(x, y, t)          ((x) + (((y) - (x)) * (t)))

/* Index a buffer that is 2D with an x and y coord */
#define INDEX_XY(x, y, width)  ((x) + ((y) * (width)))

/* Swap two variables of the same type */
#define SWAP(x, y)             do{\
    __typeof__(x) tmp = x;\
    x = y;\
    y = tmp;\
} while(0)

/* Const char * from boolean value */
#define BOOL_STR(x)            ((x) ? "true" : "false")
/* Hex char from number */
#define HEX_CHAR(x)            ((x) < 10 ? '0' + (x) : 'A' + (x) - 10)

#endif /* _CORE_MACROS_H */
