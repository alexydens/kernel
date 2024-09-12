/* Include guard */
#if !defined(GRAPHICS_VGA_H)
#define GRAPHICS_VGA_H

/* Includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"
#include "port_io.h"

/* Consts */
#define VGA_WIDTH       80                    /* Width in chars of screen */
#define VGA_HEIGHT      25                    /* Height in chars of screen */
#define VGA_TAB_WIDTH   8                     /* Width in chars of a tab */
#define VGA_REG_CTRL    0x3D4                 /* Control register address */
#define VGA_REG_DATA    0x3D5                 /* Data register address */

/*
All the values for the different vga text colors.
SOURCE: https://wiki.osdev.org/Bare_Bones
*/
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/* Clear vga buffer */
extern void graphics_vga_clear(char c);
/* Set color used for putc */
extern void graphics_vga_set_color(enum vga_color fg, enum vga_color bg);
/* Sets cursor position */
extern void graphics_vga_set_cursor(uint8_t x, uint8_t y);
/* Write character to vga buffer */
extern void graphics_vga_putc(char c);
/* Write a string to the screen */
extern void graphics_vga_puts(char *str);
/* Change vga graphics mode */
extern void graphics_vga_set_mode(uint8_t mode);

#endif /* GRAPHICS_VGA_H */
