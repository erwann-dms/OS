#include <stdint.h>

// Lit un octet depuis un port
uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Handler du clavier (IRQ1)
void keyboard_handler() {
    uint8_t scancode = inb(0x60);  // Lit le scancode
    char key = "?1234567890-=..."[scancode];  // Table de conversion
    print_char(key);  // Affiche la touche (à implémenter dans vga.c)
}