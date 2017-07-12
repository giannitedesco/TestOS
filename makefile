#
# Makefile for TestOS
#
# Compiler: 	GCC 
# Assembler: 	NASM
# Linker: 		LD
#

TARGET = testos.bin
DEPS = environment.o boot.o kernel.o

#Assembly configuration
NASM = nasm
ASM_FLAGS = -f elf32

#C compilation configuration
CC = gcc
CFLAGS = -std=gnu99 -m32 -ffreestanding -O2 -Wall -Wextra

#Linker configuration
LD = ld
LD_FLAGS = -m elf_i386 -T linker.ld 

#all rules
.PHONY : all
all : $(TARGET)
testos : $(TARGET)

#Object-source dependencies
environment.o : environment.asm
boot.o : boot.asm
kernel.o : kernel.c

#Rules
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o : %.asm
	$(NASM) $(ASM_FLAGS) $< -o $@	

testos.bin: $(DEPS)
	$(LD) -o $@ $(LD_FLAGS) $?

.PHONY: clean
clean:
	rm -f *.o
	rm -f testos.bin