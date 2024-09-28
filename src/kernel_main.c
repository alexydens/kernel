/* Includes */
#include <core/types.h>
#include <ext/multiboot.h>

/* Entry point */
void kernel_main(multiboot_info_t *mb_info) {

  /* Hang when finished */
  __asm__ __volatile__ ("cli;hlt");
  while (1);
  /* Stop compiler warning 'unused variable' */
  (void)mb_info;
}
