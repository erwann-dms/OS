// kernel/kmalloc.c
#include <stddef.h>

#define HEAP_SIZE 0x100000
static uint8_t heap[HEAP_SIZE];
static size_t heap_ptr = 0;

void* kmalloc(size_t size) {
    if (heap_ptr + size > HEAP_SIZE) return NULL;
    void* ptr = &heap[heap_ptr];
    heap_ptr += size;
    return ptr;
}

void kfree(void* ptr) {
    // Simplifié (pas de gestion de fragmentation)
}