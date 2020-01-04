# os
Custom OS written from scratch.  Heavily based on Nick Blundell's tutorial "Writing a Simple Operating System From Scratch".

```
.
├── LICENSE
├── Makefile
├── README.md
├── bin
│   ├── bootsect.bin
│   ├── kernel.bin
│   └── os-image.bin
├── boot
│   ├── 01_boot_sect.asm
│   ├── 02_hello_world.asm
│   ├── 03_allocate_char.asm
│   ├── 04_stack.asm
│   ├── 05_function.asm
│   ├── 07_data_segment.asm
│   ├── 08_disk_read.asm
│   ├── 09_gdt.asm
│   ├── 10_32bit_protected_mode.asm
│   ├── 11_kernel.asm
│   ├── bootsect.asm
│   ├── kernel_entry.asm
│   └── print_string.asm
├── cpu
│   ├── idt.h
│   ├── interrupt.asm
│   ├── isr.c
│   ├── isr.h
│   ├── timer.h
│   └── types.h
├── drivers
│   ├── keyboard.h
│   ├── ports.h
│   └── screen.h
├── kernel
│   ├── kernel.c
│   └── output
└── libc
    ├── function.h
    ├── mm.h
    └── string.h

6 directories, 33 files

```
