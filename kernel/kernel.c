#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/idt.h"


void __kernel_main() {
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
