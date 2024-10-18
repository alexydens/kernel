/* Implements mem/vmm.h */
#include <mem/vmm.h>

/* Globals */
/* The physical address of the current page directory */
static u32 current_pd;
/* Space to load the page directory that is being edited */
volatile u32 *edit_pd = (u32 *)0xc03fe000;
/* Space to load the page table that is being edited */
volatile u32 *edit_pt = (u32 *)0xc03ff000;

/* Initialize the virtual memory manager */
bool vmm_init(void) {
  /* Set current page directory to _init_PD */
  current_pd = (u32)((void*)_init_PD);

  return true;
}

/* Create a new page directory */
u32 vmm_create_page_directory(void) {
  /* Get a free page */
  u32 pd = pfa_get_frame();
  /* Load it into edit_pd */
  _init_PT0[1022] = pd | 0x3;

  /* Set each entry to non-present, read/write */
  for (u32 i = 0; i < 1024; i++) edit_pd[i] = 0x2;
  /* Copy over the kernel page table */
  edit_pd[0x300] = ((u32)_init_PT0-0xc0000000) | 0x3;

  /* Unload it, editing done */
  _init_PT0[1022] = 0x2;

  return pd;
}
/* Switch to a page directory */
void vmm_switch_page_directory(u32 pd) {
  /* Set current page directory */
  current_pd = pd;
  /* Move into cr3 */
  __asm__ __volatile__ ("mov %0, %%eax" :: "r"(pd));
  __asm__ __volatile__ ("mov %eax, %cr3");
  __asm__ __volatile__ ("lea 1f, %eax");
  __asm__ __volatile__ ("jmp *%eax");
  __asm__ __volatile__ ("1:");
}
/* Delete a page directory */
void vmm_delete_page_directory(u32 pd) {
  /* Load in the page directory */
  _init_PT0[1022] = pd | 0x3;

  /* Loop over page tables */
  for (u32 i = 0; i < 0x300; i++) {
    /* Skip non-present entries */
    if (!(edit_pd[i] & 0x1)) continue;
    /* Load in the page table */
    _init_PT0[1023] = edit_pd[i] | 0x3;

    /* Loop over entries */
    for (u32 j = 0; j < 1024; j++) {
      /* Skip non-present entries */
      if (!(edit_pt[j] & 0x1)) continue;
      /* Free the page */
      pfa_free_frame(edit_pt[j] & ~(0xfff));
    }

    /* Unload the page table */
    _init_PT0[1023] = 0x2;
    /* Free the page table page frame */
    pfa_free_frame(edit_pd[i] & ~(0xfff));
  }

  /* Unload the page directory */
  _init_PT0[1022] = 0x2;
  /* Free the page directory page frame */
  pfa_free_frame(pd);
}

/* Map a page of virtual memory */
void vmm_map_page(u32 virtual_addr, u8 type) {
  /* Load in the page directory */
  _init_PT0[1022] = current_pd | 0x3;
  /* Load in the page table */
  if (!(edit_pd[virtual_addr >> 22] & 0x1)) {
    edit_pd[virtual_addr >> 22] = pfa_get_frame() | 0x3;
    _init_PT0[1023] = edit_pd[virtual_addr >> 22] | 0x3;
    for (u32 i = 0; i < 1024; i++) edit_pt[i] = 0x2;
  } else _init_PT0[1023] = edit_pd[virtual_addr >> 22] | 0x3;

  /* Set the entry */
  u32 page = pfa_get_frame();
  switch (type) {
    case VMM_PAGE_TYPE_KERNEL:
      edit_pt[(virtual_addr >> 12) & 0x3ff] = page | 0x3;
      break;
    case VMM_PAGE_TYPE_USER:
      edit_pt[(virtual_addr >> 12) & 0x3ff] = page | 0x7;
      break;
  }

  /* Unload the page table */
  _init_PT0[1023] = 0x2;
  /* Unload the page directory */
  _init_PT0[1022] = 0x2;
}
/* Unmap a page of virtual memory */
void vmm_unmap_page(u32 virtual_addr) {
  /* Load in the page directory */
  _init_PT0[1022] = current_pd | 0x3;
  /* Load in the page table */
  _init_PT0[1023] = edit_pd[virtual_addr >> 22] | 0x3;

  /* Set the entry */
  edit_pt[(virtual_addr >> 12) & 0x3ff] = 0x2;

  /* Unload the page table */
  _init_PT0[1023] = 0x2;
  /* Unload the page directory */
  _init_PT0[1022] = 0x2;
}
