# Source files (asm, c, maybe some C++)
SRC_DIR=src
# Binary files (e.g. image)
BIN_DIR=bin
# Object files
OBJ_DIR=obj
# Cross compiler and tools
CROSS_DIR=../toolchain/build-i686-elf

# GNU Compiler Collection (C compiler)
CC=$(CROSS_DIR)/bin/i686-elf-gcc
# C PreProcessor
CPP=$(CROSS_DIR)/bin/i686-elf-cpp
# C++ Compiler
CXX=$(CROSS_DIR)/bin/i686-elf-g++
# Assembler
AS=$(CROSS_DIR)/bin/i686-elf-as
# Linker
LD=$(CROSS_DIR)/bin/i686-elf-ld
# Archiver
AR=$(CROSS_DIR)/bin/i686-elf-ar
# Strip (remove info from obj file)
STRIP=$(CROSS_DIR)/bin/i686-elf-strip
# Objcopy (copy obj files, translate obj files)
OBJCOPY=$(CROSS_DIR)/bin/i686-elf-objcopy

# C Compiler flags
CFLAGS = -std=c11 -ffreestanding -Wall -Wextra -Wpedantic
# C++ Compiler flags
CXXFLAGS = -std=c++17 -ffreestanding -Wall -Wextra -Wpedantic -fno-exceptions -fno-rtti
# Linker flags
LDFLAGS = -Tlinker.ld -ffreestanding -nostdlib -O2 -lgcc

# Sources in C
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Sources in asm
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))
OBJECTS += $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASM_SOURCES))

# Compile C code
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile assembly code
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) -o $@ $<

# Link into main binary
$(BIN_DIR)/main.bin: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Make image
$(BIN_DIR)/main.iso: $(BIN_DIR)/main.bin
	rm -rf isodir
	mkdir -p isodir/boot/grub
	cp $(BIN_DIR)/main.bin isodir/boot/main.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/main.iso isodir

# Phony targets
.PHONY: build clean test

# Build
build: $(BIN_DIR)/main.iso

# Test
test: $(BIN_DIR)/main.iso
	qemu-system-i386 -cdrom $(BIN_DIR)/main.iso

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf isodir
