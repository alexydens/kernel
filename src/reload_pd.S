.globl reload_pd
.type reload_pd, @function
.align 4
reload_pd:
  mov %cr3, %eax
  mov %eax, %cr3
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0
  ret
.size reload_pd, .-reload_pd
