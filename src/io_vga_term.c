/* Implements io/vga_term.h */
#include <io/vga_term.h>

/* Consts */
/* Dimensions of the screen in characters */
#define VGA_TERM_COLS             80
#define VGA_TERM_ROWS             25
/* Size of terminal buffer in bytes */
#define VGA_TERM_BUF_SIZE    (VGA_TERM_COLS * VGA_TERM_ROWS * 2)
/* Size of terminal buffer in characters */
#define VGA_TERM_SIZE            (VGA_TERM_COLS * VGA_TERM_ROWS)
/* Width of tab characters */
#define VGA_TAB_WIDTH             8
/* Ports for VGA card needed for text mode */
#define VGA_TERM_REG_CTRL         0x3D4
#define VGA_TERM_REG_DATA         0x3D5

/* Global variables */
static u16 *_vga_term_mem = (u16 *)0xc03ff000;
static u16 *_vga_term_cursor = (u16 *)0xc03ff000;
static u8 _vga_color = 15;

/* Helpers */
/* Get character from color */
static inline u16 _get_char(u8 c, u8 color) {
  return c | color << 8;
}
/* Get color from fg and bg */
static inline u8 _get_color(u8 fg, u8 bg) {
  return fg | bg << 4;
}
/* Update the cursor position */
static inline void _update_cursor(void) {
  port_outb(VGA_TERM_REG_CTRL, 14);
  port_outb(VGA_TERM_REG_DATA, 
      (u8)((_vga_term_cursor - _vga_term_mem) >> 8));
  port_outb(VGA_TERM_REG_CTRL, 15);
  port_outb(VGA_TERM_REG_DATA, 
      (u8)(_vga_term_cursor - _vga_term_mem));
}
/* Put one character to the screen */
static inline void _putc(char c) {
  if (_vga_term_cursor >= _vga_term_mem + VGA_TERM_SIZE) {
    memcpy(
        _vga_term_mem,
        _vga_term_mem + VGA_TERM_COLS,
        (VGA_TERM_SIZE - VGA_TERM_COLS) * 2
    );
    for (
        u16 *i = _vga_term_mem + VGA_TERM_SIZE - VGA_TERM_COLS;
        i < _vga_term_mem + VGA_TERM_SIZE;
        i++
    ) {
      *i = _get_char(' ', _vga_color);
    }
    _vga_term_cursor -= VGA_TERM_COLS;
  }
  switch (c) {
    case '\n':
      _vga_term_cursor += VGA_TERM_COLS;
      break;
    case '\r':
      _vga_term_cursor -=
        (int)(_vga_term_cursor - _vga_term_mem) % VGA_TERM_COLS;
      break;
    case '\t':
      _vga_term_cursor += VGA_TAB_WIDTH
        - ((int)(_vga_term_cursor - _vga_term_mem) % VGA_TAB_WIDTH);
      break;
    default:
      *_vga_term_cursor++ = _get_char(c, _vga_color);
  }
}

/* Clear vga text buffer with character c */
void vga_term_clear(char c) {
  char char_used = c == 0 ? ' ' : c;
  u16 *vga_term_cursor = _vga_term_cursor;
  for (size_t i = 0; i < VGA_TERM_SIZE; i++) {
    *vga_term_cursor++ = _get_char(char_used, _vga_color);
  }
}
/* Set color for vga text functions */
void vga_term_set_color(u8 fg, u8 bg) {
  _vga_color = _get_color(fg, bg);
}
/* Set cursor position for vga text functions */
void vga_term_set_cursor(u8 x, u8 y) {
  /* TODO: Validate with assertions */
  _vga_term_cursor = _vga_term_mem + (y * VGA_TERM_COLS) + x;
}
/* Write character to vga text buffer */
void vga_term_putc(char c) {
  _putc(c);
  _update_cursor();
}
/* Write a string (null terminated) to the vga text buffer */
void vga_term_puts(char *str) {
  while (*str) {
    _putc(*str++);
  }
  _update_cursor();
}
