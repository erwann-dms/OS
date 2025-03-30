// Déclaration des fonctions externes
extern void init_vga();
extern void init_idt();

void kernel_main() {
    init_vga();      // Initialise l'écran
    init_idt();      // Active les interruptions

    while (1) {      // Boucle infinie
        asm("hlt");  // Économise l'énergie CPU
    }
}