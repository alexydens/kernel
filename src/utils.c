/* Implements utils.h */
#include "utils.h"

/*
extern void graphics_vga_display_bsod(void) {
A kernel panic screen (you should be rsod, but your acronymn forbids me to
interpret that you are so).
NOTE: This is a kernel panic SCREEN, not the kernel panic itself. It will NOT
stop the program execution, it will NOT exit safely. It just returns when it is
done.
PS: I've done some refactoring, and don't need this comment anymore, but i'm
going to keep it, because i thought it was funny. I'm not sure what i was
thinking when i wrote it :)
PS2: One day i will have to remove this all, if this ever scales up. By that
point, hopefully i won't be relying on this level of debugging any more. At the
very least a form of error message (enumerated?) should be added. It doesn't 
bode well that this is my longest comment so far... perhaps i have the wrong
hobby.
*/
static void _display_bsod(void) {
  uint8_t color = 76;
  uint16_t ch = '!' | color << 8;
  uint16_t *cur = (uint16_t *)0xb8000;
  for (size_t i = 0; i < 80 * 25; i++) {
    *cur = ch;
    cur++;
  }
  cur = ((uint16_t *)0xb8000) + 13 * 80 + 20;
  const char msg[] = "Yay! You broke the kernel! Time to debug!";
  color = 15;
  for (size_t i = 0; i < sizeof(msg)-1; i++) {
    *cur = msg[i] | color << 8;
    cur++;
  }
}

/*
Kernel panic - BSOD type thing and the OS will brick up. Hope i can recover
from a reboot...
*/
void kernel_panic(void) {
  _display_bsod();
  while (true) {}
}
