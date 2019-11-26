#include "../drivers/screen.h"
#include "../cpu/isr.h"

void __kernel_main() {
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}

void main() {
    char* screen = (char*) 0xb8000;

    clear_screen();

    *screen = 'h';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'e';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'l';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'l';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'o';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = ' ';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'w';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'o';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'r';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'l';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = 'd';
    screen++;
    *screen = 0x0f; 
    screen++;
    *screen = ' ';
    screen++;
    *screen = 0x0f; 
    screen++;

/*
    for (int i = 0; i < 20; i+=2) {
      *(screen + (i * 2)) = 'B';
      *(screen + (i * 2) + 1) = 0x0f;
    }
*/
}
