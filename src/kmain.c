/* Includes */

/* Entry point */
void kernel_main(unsigned int mb_info_addr) {
  *(unsigned short *)0xc03ff000 = 'A' | (1 << 8);
}
