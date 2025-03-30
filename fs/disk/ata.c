// fs/disk/ata.c
#include "../../drivers/ata.h"

void disk_read(uint32_t lba, uint8_t *buffer, uint8_t sector_count) {
    ata_read(lba, buffer, sector_count);
}