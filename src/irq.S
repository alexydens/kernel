.extern irq_handler_common
.globl irq_common
.align 4
irq_common:
  pushl %esp
  call irq_handler_common
  popl %eax
  add $8, %esp
  iret
.size irq_common, .-irq_common

.macro irq index
  .global _irq_\index
  .type _irq_\index, @function
  .align 4
  _irq_\index:
    push $\index
    push $(\index + 32)
    jmp irq_common
  .size _irq_\index, .-_irq_\index
.endm

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15
