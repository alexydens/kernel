/* Implements graphics_vga.h */
#include "graphics_vga.h"

/* Global state */
static uint16_t *_vga_mem = (uint16_t *)0xb8000;
static uint16_t *_vga_cursor = (uint16_t *)0xb8000;
static uint8_t _vga_color = 15;                /* 15 | 0<<4 (white on black) */

/* Gets a color from a foreground and background */
static inline uint8_t _get_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

/* Gets a display char from the character and color */
static inline uint16_t _get_char(uint8_t c, uint8_t color) {
  return c | color << 8;
}

/* Updates cursor position to position of _vga_cursor */
static inline void _update_cursor(void) {
  port_out_byte(VGA_REG_CTRL, 14);
  port_out_byte(VGA_REG_DATA, (uint8_t)((_vga_cursor - _vga_mem) >> 8));
  port_out_byte(VGA_REG_CTRL, 15);
  port_out_byte(VGA_REG_DATA, (uint8_t)(_vga_cursor - _vga_mem));
}

/* Clears the screen */
void graphics_vga_clear(char c) {
  char char_used = c == 0 ? ' ' : c;
  uint16_t *vga_cursor = _vga_cursor;
  for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    *vga_cursor++ = _get_char(char_used, _vga_color);
  }
}

/* Sets the foreground and background colors */
void graphics_vga_set_color(enum vga_color fg, enum vga_color bg) {
  _vga_color = _get_color(fg, bg);
}

/* Sets cursor position */
void graphics_vga_set_cursor(uint8_t x, uint8_t y) {
  KERNEL_ASSERT(x < VGA_WIDTH && y < VGA_HEIGHT);
  _vga_cursor = _vga_mem + (y * VGA_WIDTH) + x;
}

/* Writes a character to the screen */
static inline void _putc(char c) {
  if (_vga_cursor >= _vga_mem + VGA_WIDTH * VGA_HEIGHT) {
    memcpy(
        _vga_mem,
        _vga_mem + VGA_WIDTH,
        ((VGA_WIDTH * VGA_HEIGHT) - VGA_WIDTH) * 2
    );
    for (
        uint16_t *i = _vga_mem + (VGA_WIDTH * VGA_HEIGHT) - VGA_WIDTH;
        i < _vga_mem + (VGA_WIDTH * VGA_HEIGHT);
        i++
    ) {
      *i = _get_char(' ', _vga_color);
    }
    _vga_cursor -= VGA_WIDTH;
  }
  switch (c) {
    case '\n':
      _vga_cursor += VGA_WIDTH;
      break;
    case '\r':
      _vga_cursor -= (int)(_vga_cursor - _vga_mem) % VGA_WIDTH;
      break;
    case '\t':
      _vga_cursor +=
        VGA_TAB_WIDTH - ((int)(_vga_cursor - _vga_mem) % VGA_TAB_WIDTH);
      break;
    default:
      *_vga_cursor++ = _get_char(c, _vga_color);
  }
}
/* Writes a character to the screen */
void graphics_vga_putc(char c) {
  _putc(c);
  _update_cursor();
}

/* Write a string to the screen */
void graphics_vga_puts(char *str) {
  while (*str) {
    _putc(*str++);
  }
  _update_cursor();
}
