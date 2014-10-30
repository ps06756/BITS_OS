#!/bin/bash 
nasm -f bin bootsect.asm -o bootsect.bin  
qemu-system-i386 -hdc disk.img bootsect.bin 
