/* Entry point for the kernel */
void kernel_main(void) {
  *(unsigned short *)0xc03ff000 = 'A' | (1 << 8);
}
