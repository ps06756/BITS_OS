#!/bin/bash 
nasm -f bin bootsect.asm -o bootsect.bin  
qemu-system-i386 -hdd disk.img bootsect.bin 
