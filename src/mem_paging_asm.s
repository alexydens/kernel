.globl flush_pagedir
.type flush_pagedir, @function
.align 4
flush_pagedir:
  push %ebp
  mov %esp, %ebp
  mov 8(%esp), %eax
  mov %eax, %cr3
  mov %ebp, %esp
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0
  mov %ebp, %esp
  pop %ebp
  ret
