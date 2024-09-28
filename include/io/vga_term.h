/* Include guard */
#ifndef _IO_VGA_TERM_H
#define _IO_VGA_TERM_H

/* Includes */
#include <core/types.h>
#include <core/utils.h>
#include <io/port.h>

/* Consts */
/* All the different color options for this mode */
#define VGA_TERM_COLOR_BLACK           0
#define VGA_TERM_COLOR_BLUE            1
#define VGA_TERM_COLOR_GREEN           2
#define VGA_TERM_COLOR_CYAN            3
#define VGA_TERM_COLOR_RED             4
#define VGA_TERM_COLOR_MAGENTA         5
#define VGA_TERM_COLOR_BROWN           6
#define VGA_TERM_COLOR_LIGHT_GREY      7
#define VGA_TERM_COLOR_DARK_GREY       8
#define VGA_TERM_COLOR_LIGHT_BLUE      9
#define VGA_TERM_COLOR_LIGHT_GREEN     10
#define VGA_TERM_COLOR_LIGHT_CYAN      11
#define VGA_TERM_COLOR_LIGHT_RED       12
#define VGA_TERM_COLOR_LIGHT_MAGENTA   13
#define VGA_TERM_COLOR_LIGHT_BROWN     14
#define VGA_TERM_COLOR_WHITE           15

/* Function prototypes */
/* Clear VGA text buffer with character c */
extern void vga_term_clear(char c);
/* Set color for VGA text functions */
extern void vga_term_set_color(u8 fg, u8 bg);
/* Set cursor position for VGA text functions */
extern void vga_term_set_cursor(u8 x, u8 y);
/* Write character to VGA text buffer */
extern void vga_term_putc(char c);
/* Write a null terminated string to the VGA text buffer */
extern void vga_term_puts(char *str);

#endif /* _IO_VGA_TERM_H */
