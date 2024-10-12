# Kernel
I am writing a kernel for the x86_64 architecture from scratch in the C
programming language. At the moment, it has to following specs, and is a work
in progress.
- Multiboot-compatible: As such, GRUB can be used, or any other multiboot
bootloader.
- C11: it uses the C11 standard.
- 32-bit: it makes use of a 32-bit address space.
- Higher-half: the kernel is stored in the higher half of virtual address space,
from 0xc0000000 to 0xffffffff.
