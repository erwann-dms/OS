// kernel/shell.c
#include "vga.h"
#include "string.h"

#define BUFFER_SIZE 100

char input_buffer[BUFFER_SIZE];
int buffer_pos = 0;

void read_input() {
    char key;
    while ((key = keyboard_read()) != '\n') {  // À implémenter dans keyboard.c
        if (key == '\b' && buffer_pos > 0) {   // Backspace
            buffer_pos--;
            print_char('\b');
        }
        else if (buffer_pos < BUFFER_SIZE - 1) {
            input_buffer[buffer_pos++] = key;
            print_char(key);
        }
    }
    input_buffer[buffer_pos] = '\0';
    buffer_pos = 0;
}

void shell() {
    pci_detect_ne2000();
    ne2000_init();
    ext2_init();
    print("Bienvenue dans MyOS!\n");
    while (1) {
        print("myos> ");
        read_input();

        if (strcmp(input_buffer, "help") == 0) {
            print("\nCommandes: help, ls, cat, ping, gui, win, clear, reboot\n");
        }
        else if (strcmp(input, "ls") == 0) {
            ext2_list_dir(2);  // Inode 2 = racine
        }
        else if (strcmp(input, "cat") == 0) {
            uint32_t size;
            uint8_t* data = ext2_read_file(parse_inode(input), &size);
            
            for (uint32_t i = 0; i < size; i++) {
                print_char(data[i]);
            }
            
            kfree(data);
        }
        else if (strcmp(input_buffer, "win") == 0) {
            create_window(100, 100, 200, 150, "Ma Fenêtre");
            print("Fenêtre créée!\n");
        }
        else if (strcmp(input_buffer, "gui") == 0) {
            vesa_init();
            draw_pixel(100, 100, 0x00FF0000);  // Pixel rouge
            print("Pixel dessiné!\n");
        }
        else if (strcmp(input_buffer, "ping") == 0) {
            uint8_t packet[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // Broadcast ARP
            ne2000_send_packet(packet, sizeof(packet));
            print("Paquet envoyé!\n");
        }
        else if (strcmp(input_buffer, "clear") == 0) {
            clear_screen();
        }
        else {
            print("\nCommande inconnue. Tapez 'help'.\n");
        }
    }
}