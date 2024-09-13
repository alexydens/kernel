.extern isr_handler_common
.globl isr_common
.align 4
isr_common:
  call isr_handler_common
  iret
.size isr_common, .-isr_common

.macro isr_noerr index
  .global isr_\index
  .type isr_\index, @function
  .align 4
  isr_\index:
    push $0
    push $\index
    jmp isr_common
  .size isr_\index, .-isr_\index
.endm
.macro isr_err index
  .global isr_\index
  .type isr_\index, @function
  .align 4
  isr_\index:
    push $\index
    jmp isr_common
  .size isr_\index, .-isr_\index
.endm

isr_noerr 0
isr_noerr 1
isr_noerr 2
isr_noerr 3
isr_noerr 4
isr_noerr 5
isr_noerr 6
isr_noerr 7
isr_err 8
isr_noerr 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr_noerr 15
isr_noerr 16
isr_noerr 17
isr_noerr 18
isr_noerr 19
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_noerr 30
isr_noerr 31

