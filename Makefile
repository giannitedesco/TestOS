#
# Makefile for TestOS
#
# Compiler: 	GCC 
# Assembler: 	NASM
# Linker: 		LD
#

TARGET := testos.bin
ALL_OBJ := environment.o \
		boot.o \
		kernel.o \
		string.o
ALL_DEP := $(patsubst %.o,.%.d,$(ALL_OBJ))

#Assembly configuration
NASM := nasm
ASM_FLAGS := -f elf32

#C compilation configuration
CC := gcc
CFLAGS := -std=gnu99 -m32 -ffreestanding -O2 -Wall -Wextra

#Linker configuration
LD := ld
LD_FLAGS := -m elf_i386 -T linker.ld

#all rules
.PHONY : all testos clean
all : $(TARGET)
testos : $(TARGET)

#Rules
%.o : %.c
	@echo " [C] $<"
	@$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o, .%.d, $@) \
		-MT $(patsubst .%.d, %.o, $@) \
		-c -o $(patsubst .%.d, %.o, $@) $<

%.o : %.asm
	@echo " [NASM] $<"
	@$(NASM) $(ASM_FLAGS) $< -o $@	

testos.bin: $(ALL_OBJ)
	@echo " [NASM] $@"
	@$(LD) -o $@ $(LD_FLAGS) $^

clean:
	rm -f *.o
	rm -f testos.bin

ifneq ($(MAKECMDGOALS),clean)
-include $(ALL_DEP)
endif
