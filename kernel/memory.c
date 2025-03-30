#include <stdint.h>

// Structure d'une entrée de page (32 bits)
typedef struct {
    uint32_t present : 1;   // Page présente en mémoire
    uint32_t rw : 1;        // Lecture/Écriture
    uint32_t user : 1;      // Niveau de privilège
    uint32_t reserved : 9;  // Réservé
    uint32_t frame : 20;    // Adresse physique
} page_table_entry;

// Initialise la pagination
void init_paging() {
    // 1. Crée un répertoire de pages (Page Directory)
    // 2. Configure les tables de pages (Page Tables)
    // 3. Active la pagination via CR0 et CR3
    asm volatile("mov %%cr3, %0" : : "r"(page_directory));
    asm volatile("mov %cr0, %eax; or $0x80000000, %eax; mov %eax, %cr0");
}

// kernel/memory.c
#include "kheap.h"

#define HEAP_SIZE 1024 * 1024  // 1 Mo

static char heap[HEAP_SIZE];
static size_t heap_ptr = 0;

void heap_init() {
    heap_ptr = 0;
}

void *kmalloc(size_t size) {
    if (heap_ptr + size > HEAP_SIZE) return NULL;
    void *ptr = &heap[heap_ptr];
    heap_ptr += size;
    return ptr;
}

void kfree(void *ptr) {
    // Simplifié (pas de gestion de fragmentation)
}