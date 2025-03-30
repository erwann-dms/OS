// kernel/task.h
#pragma once

typedef struct {
    uint32_t eax, ebx, ecx, edx, esp, ebp, eip, eflags;
} task_registers;

typedef struct {
    task_registers regs;
    uint8_t stack[4096];  // Stack de 4 Ko
} task;

task g_tasks[2];
int g_current_task = 0;