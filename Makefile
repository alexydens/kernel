# Directories
SRC_DIR=src
INC_DIR=include
BIN_DIR=bin
OBJ_DIR=obj
LOG_DIR=log
GRUB_ISODIR=isodir
CROSS_DIR=../toolchain/build-i686-elf

# Toolchain
CC=$(CROSS_DIR)/bin/i686-elf-gcc
CXX=$(CROSS_DIR)/bin/i686-elf-g++
AS=$(CROSS_DIR)/bin/i686-elf-as
LD=$(CROSS_DIR)/bin/i686-elf-ld
AR=$(CROSS_DIR)/bin/i686-elf-ar
STRIP=$(CROSS_DIR)/bin/i686-elf-strip
OBJCOPY=$(CROSS_DIR)/bin/i686-elf-objcopy

# C compiler flags
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
CFLAGS += -ffreestanding
CFLAGS += -I$(INC_DIR)
# C++ compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
CXXFLAGS += -ffreestanding
CXXFLAGS += -fno-exceptions -fno-rtti
CXXFLAGS += -I$(INC_DIR)
# Linker flags
LDFLAGS = -Tlinker.ld

# Source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
CXX_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.S)
# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))
OBJECTS += $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CXX_SOURCES))
OBJECTS += $(patsubst $(SRC_DIR)/%.S,$(OBJ_DIR)/%.o,$(ASM_SOURCES))

# Compile sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S | $(OBJ_DIR)
	$(AS) -o $@ $<

# Link objects
$(BIN_DIR)/main.bin: $(OBJECTS) | $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $^

# GRUB image
$(BIN_DIR)/main.iso: $(BIN_DIR)/main.bin
	rm -rf $(GRUB_ISODIR)
	mkdir -p $(GRUB_ISODIR)/boot/grub
	cp $(BIN_DIR)/main.bin $(GRUB_ISODIR)/boot/main.bin
	cp grub.cfg $(GRUB_ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/main.iso $(GRUB_ISODIR)

# Directories
$(BIN_DIR):
	mkdir -p $@
$(OBJ_DIR):
	mkdir -p $@
$(LOG_DIR):
	mkdir -p $@

# Phony targets
.PHONY: build clean test test_headless

# Build bin file
build: $(BIN_DIR)/main.bin

# Test with qemu and GRUB
test: $(BIN_DIR)/main.iso | $(LOG_DIR)
	qemu-system-i386 -cdrom $(BIN_DIR)/main.iso -m 4096M \
		-chardev stdio,id=char0,logfile=$(LOG_DIR)/serial_com1.log,signal=off \
		-serial chardev:char0

# Clean up project folder
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(LOG_DIR)
	rm -rf $(GRUB_ISODIR)
