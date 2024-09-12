/* Implements mem_paging.h */
#include "mem_paging.h"

/* Globals */
static uint32_t page_dir[1024] __attribute__((aligned(0x1000)));
static uint32_t page_tab[1024] __attribute__((aligned(0x1000)));

/* asm */
extern void flush_pagedir(unsigned int*);

/* Initialize and load the PD and PTs */
void mem_paging_init(void) {
  /* Initialize page directory */
  for (int i = 0; i < 1024; i++) {
    /*
    - bit 0: present = 0.
    - bit 1: !readonly = 1.
    - bit 2: supervisor: 0.
     */
    page_dir[i] = 0x00000002;
  }

  /* Initialize page table */
  for (int i = 0; i < 1024; i++) {
    /*
    - bit 0: present = 1.
    - bit 1: !readonly = 1.
    - bit 2: supervisor: 0.
     */
    page_tab[i] = (i * 0x1000) | 0x00000003;
  }
  /*
  - bit 0: present = 1.
  - bit 1: !readonly = 1.
  - bit 2: supervisor: 0.
   */
  page_dir[0] = (uint32_t)page_tab | 0x00000003;

  /* Flush page directory */
  flush_pagedir((unsigned int*)page_dir);
}
