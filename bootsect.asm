[org 0x7c00] ; we expect the code to be loaded at this position always and all the addresses expressed are relative to this. 
; This is the boot sector and will initially contain the only small relevant code. 
; We will have a full elf32 executable in the disk through which we will be booting our operating system and load the relevant part of the operating system in the ram. We will also support modules in the same way, 
; O means that the operating system has started executing the code, and now it will check for the protected mode enable code.   
; First setup the stack.
; ----------------------------------------------STACK_SETUP(1024 bytes)----------------------------------------------------------;  
mov ebp, 0x8000 
mov esp, ebp 
;-----------------------------------------------TELETYPE_SETUP-------------------------------------------------------------------;
mov al, 'L'
call p_char 
call disk_status
jmp $ 
;----------------------------------------------METHODS_DEFINED_HERE-------------------------------------------------------------;
fail:
	add ah, '0'
	mov al, ah 
	call p_char
	ret
suc:
	mov al, 'S' 
	call p_char 
	ret 
p_char:
	mov ah, 0x0e
	int 10h 
	ret 
disk_status: 
	mov dl, 81h 
	mov ah, 01  	
	je suc
	jne fail
	ret
msg db 'Hello World',0 
;-----------------------------------------------NULL_BYTES-----------------------------------------------------------------------;
times 510 - ($ - $$) db 0
;-----------------------------------------------MAGIC_NUMBER---------------------------------------------------------------------; 
dw 0xaa55 
;-----------------------------------------------THE_END--------------------------------------------------------------------------;
