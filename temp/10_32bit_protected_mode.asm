[org 0x7c00] ; bootloader offset
    mov bp, 0x9000 		; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string 	; This will be written after the BIOS messages

    call switch_to_pm
    jmp $ 				; this will actually never be executed


[bits 16]
switch_to_pm:
    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] 	; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x1 			; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_pm 	; 4. far jump by using a different segment



[bits 32]
init_pm: ; we are now using 32-bit instructions
    mov ax, DATA_SEG ; 5. update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp

    call BEGIN_PM ; 7. Call a well-known label with useful code

;[bits 32]
;BEGIN_PM: ; after the switch we will get here
;    mov ebx, MSG_PROT_MODE
;    call print_string ; Note that this will be written at the top left corner
;    jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0

%include "print_string.asm"
%include "09_gdt.asm"

; bootsector
;times 510-($-$$) db 0
;dw 0xaa55
