/* Include guard */
#ifndef CORE_PRINTF_H
#define CORE_PRINTF_H

/* Includes */
#include <core/base.h>

/* Print formatted output using provided putc */
extern void _printf(void (*putc)(char), const char *format, ...);

#endif /* CORE_PRINTF_H */
