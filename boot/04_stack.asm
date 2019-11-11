;
; A simple boot sector program that demonstrates the stack. 
;

mov ah, 0x0e  ; int 10/ah = 0eh -> scrolling teletype BIOS routine

mov bp, 0x8000  ; Set the base of the stack a little above where BIOS ; loads our boot sector - so it won’t overwrite us.
mov sp, bp

; Push some characters on the stack for later ; retreival. Note, these are pushed on as
; 16-bit values, so the most significant byte ; will be added by our assembler as 0x00.
push 'A'
push 'B' 
push 'C'

; Note, we can only pop 16-bits, so pop to bx ; then copy bl (i.e. 8-bit char) to al
; print(al)
pop bx
mov al, bl 
int 0x10

; Pop the next value 
; print(al)
pop bx
mov al, bl 
int 0x10


; To prove our stack grows downwards from bp,
; fetch the char at 0x8000 - 0x2 (i.e. 16-bits) ; print(al)
mov al, [0x7ffe] 
int 0x10

; Jump forever.
jmp $

; Padding and magic BIOS number.
times 510-($-$$) db 0 
dw 0xaa55
