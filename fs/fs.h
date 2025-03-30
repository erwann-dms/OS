// fs/fs.h
#pragma once

typedef struct {
    uint8_t boot_jump[3];
    char oem_name[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    // ... (autres champs FAT16)
} __attribute__((packed)) fat16_boot_sector;

fat16_boot_sector g_boot_sector;