.global ring3_test
.type ring3_test, @function
ring3_test:
  mov $0x23, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  mov %eax, %esp
  push $0x23
  push %eax
  pushf
  push $0x23
  push $0x1b
  push user_program

  iret

.global user_program
.type user_program, @function
user_program:
  //cli /* Should GPF */
  ret
