// drivers/ne2000.c
#include "net.h"

#define NE2000_PORT 0x300
#define NE2000_IMR  0x0F

void ne2000_init() {
    // 1. Réinitialiser la carte
    outb(NE2000_PORT + 0x1F, 0xFF);
    for (volatile int i = 0; i < 100000; i++);  // Délai

    // 2. Configurer les registres
    outb(NE2000_PORT + 0x00, 0x21);  // Stop + DMA
    outb(NE2000_PORT + NE2000_IMR, 0x00);  // Désactiver interruptions

    print("NE2000 initialisée\n");
}

void ne2000_send_packet(uint8_t *data, uint16_t len) {
    // 1. Programmer le DMA
    outb(NE2000_PORT + 0x0A, 0x00);  // Page de transmission
    outb(NE2000_PORT + 0x0C, len);   // Longueur

    // 2. Copier les données
    for (int i = 0; i < len; i++) {
        outb(NE2000_PORT + 0x10, data[i]);
    }

    // 3. Lancer l'émission
    outb(NE2000_PORT + 0x00, 0x22);  // Start + Send
}