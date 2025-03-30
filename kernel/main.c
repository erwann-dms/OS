// Adresse mémoire vidéo VGA (mode texte)
volatile char *vga = (volatile char*) 0xB8000;

void clear_screen() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga[i] = ' ';
        vga[i + 1] = 0x07;  // Gris sur noir
    }
}

void print(const char *str) {
    static int pos = 0;
    while (*str) {
        vga[pos] = *str++;
        vga[pos + 1] = 0x07;
        pos += 2;
    }
}

void main() {
    clear_screen();
    print("Hello from MyOS Kernel!");
    while (1);  // Boucle infinie
}