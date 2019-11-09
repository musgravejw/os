# os
Custom OS written from scratch.  Heavily based on Nick Blundell's tutorial "Writing a Simple Operating System From Scratch".

```
.
├── Makefile
├── README.md
├── boot
│   ├── 32bit_print.asm
│   ├── bootsect.asm
│   ├── disk.asm
│   ├── gdt.asm
│   ├── kernel_entry.asm
│   ├── print.asm
│   ├── print_hex.asm
│   └── switch_pm.asm
├── drivers
│   ├── ports.h
│   ├── screen.c
│   └── screen.h
├── kernel
│   ├── kernel.c
│   └── util.h
└── temp
    ├── 01_boot_sect.asm
    ├── 01_kernel.c
    ├── 02_hello_world.asm
    ├── 03_allocate_char.asm
    ├── 04_stack.asm
    ├── 05_function.asm
    ├── 06_hex.asm
    ├── 07_data_segment.asm
    ├── 08_disk_read.asm
    ├── 09_gdt.asm
    ├── 10_32bit_protected_mode.asm
    ├── 11_kernel.asm
    ├── notes
    └── print_string.asm

4 directories, 33 files
```
