// drivers/vesa.c
#include "gfx.h"

uint32_t *vesa_fb = (uint32_t*)0xFD000000;  // Adresse framebuffer (exemple)

void vesa_init() {
    // 1. Configurer le mode via BIOS ou Multiboot
    // (Simplifié pour l'exemple)
    print("Mode VESA 1024x768 activé\n");
}

void draw_pixel(int x, int y, uint32_t color) {
    vesa_fb[y * 1024 + x] = color;
}