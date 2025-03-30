#include <stdint.h>

// Structure d'une entrée IDT
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_entry idt[256];

// Handler d'interruption générique
void irq_handler() {
    asm volatile("pusha");  // Sauvegarde les registres
    // Vérifie quelle IRQ a été déclenchée
    asm volatile("popa");   // Restaure les registres
    asm volatile("iret");   // Retour de l'interruption
}

// Configure une entrée dans l'IDT
void idt_set_gate(uint8_t num, uint32_t handler) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = 0x08;  // Segment de code
    idt[num].flags = 0x8E;     // Présent, DPL=0, 32 bits
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

// Initialise l'IDT et active les interruptions
void init_idt() {
    // Configure les interruptions matérielles (IRQ0-IRQ15)
    for (int i = 0; i < 16; i++) {
        idt_set_gate(32 + i, (uint32_t)irq_handler);
    }
    asm volatile("lidt idt_descriptor");
    asm volatile("sti");  // Active les interruptions
}