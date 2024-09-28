# Input/Output Directory
The input/output directory contains the headers used to interface with other
devices and parts of the computer. Essentially, it contains the majority of the
drivers. Examples include:
- A VGA 80x25 text mode driver, stored in `io/vga_term.h`.
- A ported I/O driver, stored in `io/port.h`.
- A serial port driver, stored in `io/serial.h`.
- A PS2 keyboard driver using IRQ1, stored in `io/ps2kbd.h`.
