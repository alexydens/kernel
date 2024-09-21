/* Include guard */
#ifndef _VGA_TEXT_TERM_H
#define _VGA_TEXT_TERM_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include "port_io.h"
#include "utils.h"

/* Consts */
/* Dimensions of the screen in characters */
#define VGA_TEXT_TERM_COLS             80
#define VGA_TEXT_TERM_ROWS             25
/* Size of terminal buffer in bytes */
#define VGA_TEXT_TERM_BUF_SIZE (VGA_TEXT_TERM_COLS * VGA_TEXT_TERM_ROWS * 2)
/* Size of terminal buffer in characters */
#define VGA_TEXT_TERM_SIZE             (VGA_TEXT_TERM_BUF_SIZE / 2)
/* Width of tab characters */
#define VGA_TEXT_TAB_WIDTH             8
/* Ports for VGA card needed for text mode */
#define VGA_TEXT_REG_CTRL              0x3D4
#define VGA_TEXT_REG_DATA              0x3D5
/* All the different color options for this mode */
#define VGA_TEXT_COLOR_BLACK           0
#define VGA_TEXT_COLOR_BLUE            1
#define VGA_TEXT_COLOR_GREEN           2
#define VGA_TEXT_COLOR_CYAN            3
#define VGA_TEXT_COLOR_RED             4
#define VGA_TEXT_COLOR_MAGENTA         5
#define VGA_TEXT_COLOR_BROWN           6
#define VGA_TEXT_COLOR_LIGHT_GREY      7
#define VGA_TEXT_COLOR_DARK_GREY       8
#define VGA_TEXT_COLOR_LIGHT_BLUE      9
#define VGA_TEXT_COLOR_LIGHT_GREEN     10
#define VGA_TEXT_COLOR_LIGHT_CYAN      11
#define VGA_TEXT_COLOR_LIGHT_RED       12
#define VGA_TEXT_COLOR_LIGHT_MAGENTA   13
#define VGA_TEXT_COLOR_LIGHT_BROWN     14
#define VGA_TEXT_COLOR_WHITE           15

/* Clear vga text buffer with character c */
extern void vga_text_clear(char c);
/* Set color for vga text functions */
extern void vga_text_set_color(uint8_t fg, uint8_t bg);
/* Set cursor position for vga text functions */
extern void vga_text_set_cursor(uint8_t x, uint8_t y);
/* Write character to vga text buffer */
extern void vga_text_putc(char c);
/* Write a string (null terminated) to the vga text buffer */
extern void vga_text_puts(char *str);

#endif /* _VGA_TEXT_TERM_H */
