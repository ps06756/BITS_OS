# This is the make file for the BITS_OS project.
curr_dir = $(shell pwd)
inc_dir = $(curr_dir)/include
lib_dir = $(curr_dir)/lib
script = linker_script.ld
target = proc_asm.o kernel_asm.o proc_c.o kernel.o io.o string.o idt.o exception.o  
flags = -Wall -Werror -nostdinc -m32 -c -g -fno-builtin -I$(inc_dir)  # -g for debugging information. 
comp = g++
sys_obj = proc_asm.o $(lib_dir)/proc_c.o kernel_asm.o kernel.o $(lib_dir)/io.o $(lib_dir)/string.o $(lib_dir)/idt.o $(lib_dir)/exception.o  
all: $(target) 
	ld -m elf_i386  -t $(script) -o kernel.bin $(sys_obj) -nostdlib -Map os.map -Ttext 0x7e00
	qemu-system-i386 -s -kernel kernel.bin 

proc_asm.o: processor.asm 
	nasm -g -f elf processor.asm -o proc_asm.o 

kernel_asm.o: start.asm
	nasm -g -f elf start.asm -o kernel_asm.o 

proc_c.o: $(lib_dir)/processor.c
	$(comp) -o $(lib_dir)/proc_c.o $(lib_dir)/processor.c $(flags)

kernel.o: kernel.c
	$(comp) -o kernel.o kernel.c $(flags)

io.o: $(lib_dir)/io.c
	$(comp) -o $(lib_dir)/io.o $(lib_dir)/io.c $(flags) 
string.o: $(lib_dir)/string.c
	$(comp) -o $(lib_dir)/string.o $(lib_dir)/string.c $(flags)
idt.o: $(lib_dir)/idt.c
	$(comp) -o $(lib_dir)/idt.o $(lib_dir)/idt.c $(flags) 
exception.o: $(lib_dir)/exception.c
	$(comp) -o $(lib_dir)/exception.o $(lib_dir)/exception.c $(flags) 
clean:
	rm -v $(lib_dir)/*.o 
	rm -v *.o 
	rm -v kernel.bin
