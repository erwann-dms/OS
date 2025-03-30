// fs/fat16.c
#include "fs.h"
#include "ata.h"

void fat16_init() {
    // 1. Lire le secteur de boot (LBA 0)
    ata_read(0, (uint8_t*)&g_boot_sector, 1);

    // 2. Valider la signature
    if (g_boot_sector.boot_signature != 0xAA55) {
        print("Erreur: Signature FAT16 invalide!\n");
        return;
    }

    print("FAT16 initialisé avec succès!\n");
}

void fat16_list_root() {
    // 1. Calculer l'adresse du répertoire racine
    uint32_t root_dir_lba = g_boot_sector.reserved_sectors + 
                           (g_boot_sector.fat_count * g_boot_sector.sectors_per_fat);

    // 2. Lire les entrées
    fat16_entry entries[16];
    ata_read(root_dir_lba, (uint8_t*)entries, 1);

    // 3. Afficher les fichiers
    for (int i = 0; i < 16; i++) {
        if (entries[i].filename[0] == 0x00) break;  // Fin du répertoire
        if (entries[i].filename[0] == 0xE5) continue;  // Entrée supprimée

        char name[9];
        memcpy(name, entries[i].filename, 8);
        name[8] = '\0';
        print(name);
        print("\n");
    }
}