# This is the make file for the BITS_OS project.
curr_dir = $(shell pwd)
inc_dir = $(curr_dir)/include
lib_dir = $(curr_dir)/lib
script = linker_script.ld
target = kernel_asm.o kernel.o io.o string.o   
flags = -Wall -Werror -nostdinc -m32 -c -g -fno-builtin -I$(inc_dir)  # -g for debugging information. 
comp = g++
sys_obj = kernel_asm.o kernel.o $(lib_dir)/string.o $(lib_dir)/io.o  
all: $(target) 
	ld -m elf_i386  -t $(script) -o kernel.bin $(sys_obj) -nostdlib -Map os.map -Ttext 0x7e00
	strip kernel.bin  # strip of all debug symbols (to be checked for commiting) 
	qemu-system-i386 -s -kernel kernel.bin 
	cp kernel.bin kernel_plain.bin  # generate plain binary from kernel code (to be checked for commiting)  
	objcopy kernel_plain.bin -O binary 

proc_asm.o: processor.asm 
	nasm -g -f elf processor.asm -o proc_asm.o 

kernel_asm.o: start.asm
	nasm -g -f elf start.asm -o kernel_asm.o 


kernel.o: kernel.c
	$(comp) -o kernel.o kernel.c $(flags)

io.o: $(lib_dir)/io.c
	$(comp) -o $(lib_dir)/io.o $(lib_dir)/io.c $(flags) 
string.o: $(lib_dir)/string.c
	$(comp) -o $(lib_dir)/string.o $(lib_dir)/string.c $(flags)
clean:
	rm -v $(lib_dir)/*.o 
	rm -v *.o 
	rm -v *.bin
