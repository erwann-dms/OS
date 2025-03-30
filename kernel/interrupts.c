#include <stdint.h>

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_entry idt[256];

void idt_set_gate(uint8_t num, uint32_t handler) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = 0x08;  // Segment de code
    idt[num].flags = 0x8E;     // Présent, DPL=0, 32 bits
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    // Exemple: Configure une interruption clavier (IRQ1)
    idt_set_gate(33, (uint32_t)keyboard_handler);  // IRQ1 -> vecteur 33
    asm volatile("lidt idt_descriptor");
}

void keyboard_handler() {
    // Lire le scancode depuis le port 0x60
    uint8_t scancode = inb(0x60);
    // Traitement basique (à compléter)
}
