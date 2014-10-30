#!/bin/bash 
#nasm -f bin bootsect.asm -o bootsect.bin  
nasm -f elf bootsect.asm -o bootsect.o 
nasm -f elf disk.asm -o disk.o
echo "Linking now.."
ld -m elf_i386 bootsect.o -o bootsect.bin -nostdlib
objcopy bootsect.bin -O binary 
qemu-system-i386 -hdc disk.img bootsect.bin 
