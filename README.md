# A kernel from scratch for x86_64-based systems written in C and Assembly

THIS IS A WORK IN PROGRESS

## To implement
- [ ] `boot.S` file, adhering to multiboot standard, to leave space for stack
and call `kernel_main`.
- [ ] Simple VGA driver.
- [ ] Interrupt handler (IDT, IRQs).
- [ ] Create fresh GDT.
- [ ] Page allocation system (allowing for permission changing, etc).
- [ ] Task scheduling.
- [ ] Support for file system - fat32, ext4?
- [ ] Support for executable file types.
- [ ] Support for user-space programs.
- [ ] Allow kernel-space drivers to be added.
- [ ] Users and shell.
