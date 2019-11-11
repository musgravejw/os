;
; A simple boot sector program that demonstrates segment offsetting ;
25
   mov ah, 0x0e
mov al, [the_secret]
int 0x10
mov bx, 0x7c0
mov ds, bx
mov al, [the_secret] int 0x10
;
int 10/ah = 0eh -> scrolling teletype BIOS routine
; Does this print an X?
mov al, [es:the_secret] int 0x10
; Can ’t ; then
; Does
; Tell ; Does
; Does ; Jump
set ds directly , so set bx copy bx to ds.
this print an X?
the CPU to use the es (not ds) segment. this print an X?
this print an X? forever.
mov bx, mov es, mov al, int 0x10
0x7c0
bx [es:the_secret]
jmp $ the_secret:
db "X"
; Padding and magic BIOS number. times 510-($-$$) db 0
dw 0xaa55