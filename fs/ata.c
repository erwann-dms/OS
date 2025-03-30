// fs/ata.c
#include <stdint.h>

#define ATA_DATA 0x1F0
#define ATA_SECTOR_COUNT 0x1F2
#define ATA_LBA_LOW 0x1F3
#define ATA_LBA_MID 0x1F4
#define ATA_LBA_HIGH 0x1F5
#define ATA_DRIVE_SELECT 0x1F6
#define ATA_COMMAND 0x1F7

void ata_read(uint32_t lba, uint8_t *buffer, uint16_t sector_count) {
    // 1. Sélectionner le disque et le LBA
    outb(ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT, sector_count);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, 0x20);  // Commande READ

    // 2. Lire les données secteur par secteur
    for (int s = 0; s < sector_count; s++) {
        while ((inb(ATA_COMMAND) & 0x80);  // Attendre que le disque soit prêt
        for (int i = 0; i < 256; i++) {
            uint16_t data = inw(ATA_DATA);
            *buffer++ = data & 0xFF;
            *buffer++ = (data >> 8) & 0xFF;
        }
    }
}