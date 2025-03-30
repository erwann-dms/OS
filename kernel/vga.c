#define VGA_ADDR 0xB8000
volatile char *vga = (volatile char*)VGA_ADDR;

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

void init_vga() {
    clear_screen();
    print("Noyau initialise avec succes !");
}

// kernel/vga.c
void print_char(char c) {
    static int pos = 0;
    if (c == '\n') pos += 80 - (pos % 80);  // Retour à la ligne
    else {
        vga[pos] = c;
        vga[pos + 1] = 0x07;  // Couleur par défaut
        pos += 2;
    }
}