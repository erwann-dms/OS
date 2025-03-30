// kernel/task.c
#include "task.h"

void task_switch() {
    // Sauvegarde le contexte actuel
    asm volatile(
        "mov %%eax, %0\n"
        "mov %%ebx, %1\n"
        // ... (sauve tous les registres)
        : "=m"(g_tasks[g_current_task].regs.eax)
        : "m"(g_tasks[g_current_task].regs.ebx)
    );

    // Charge la tâche suivante
    g_current_task = (g_current_task + 1) % 2;
    
    asm volatile(
        "mov %0, %%eax\n"
        "mov %1, %%ebx\n"
        // ... (charge tous les registres)
        : : "m"(g_tasks[g_current_task].regs.eax),
            "m"(g_tasks[g_current_task].regs.ebx)
    );
}