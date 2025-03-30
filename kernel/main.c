// kernel/main.c
#include "shell.h"

void kernel_main() {
    init_vga();
    init_idt();
    init_keyboard();  // À implémenter
    shell();         // Lance le shell
    g_tasks[0].regs.eip = (uint32_t)&task1_entry;
    g_tasks[1].regs.eip = (uint32_t)&task2_entry;
    while (1) {
        task_switch();
        asm("sti\n hlt");  // Attend une interruption
    }
}