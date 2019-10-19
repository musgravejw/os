;
; A boot sector that prints a string using our function.
;
[org 0x7c00] ; Tell the assembler where this code will be loaded
mov bx, HELLO_MSG call print_string
mov bx, GOODBYE_MSG call print_string
jmp $
%include "print_string.asm"
; Data
HELLO_MSG:
db ’Hello, World!’, 0 ; <-- The zero on the end tells our routine
; when to stop printing characters.

GOODBYE_MSG:
db ’Goodbye!’, 0
; Padding and magic number. times 510-($-$$) db 0
dw 0xaa55