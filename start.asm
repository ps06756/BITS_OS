section .text 
[BITS 16]
; Since, we want our operating system to be multiboot compliant, we will be defining some symbols here which will be used in the "multiboot header" 
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
; Since, we are currently in 16 bit real mode, we will have to take care of memory first using the stack pointer.  
; Here, I will describe the memory map used in our Operating system. 
; 0x00000500 to 0x00007BFF  (almost 30 Kibibytes(KiB))
; 0x00007E00 to 0x0007FFFF (480.5 Kibibytes(KiB))   
; We will setup the stack in the first 30 KibiBytes above. Since, the stack grows downwards, we will be be putting base pointer in the above limit.


; Setup the stack ...............................................................................
mov ebp, 0x0007BFF 
mov esp, 0x0007BFF  
; End of setup the stack ......................................................................... 

extern kernel_main  
global _start 
_start: 
	mov eax, kernel_main 
	call eax 
	; Keep looping forever  
	cli ; Disable the interrupts.  
	jmp $ 



