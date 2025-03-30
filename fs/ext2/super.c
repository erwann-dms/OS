#include "ext2.h"
#include "../disk/ata.h"

struct ext2_superblock sb;

void ext2_init() {
    // Lire le superblock (secteur 2 en LBA)
    disk_read(2, (uint8_t*)&sb, 2);  // 2 secteurs (1024 octets)

    if (sb.s_magic != EXT2_SUPER_MAGIC) {
        print("Erreur: Pas un système EXT2 valide!\n");
        return;
    }

    print("EXT2: %d blocs, %d inodes\n", sb.s_blocks_count, sb.s_inodes_count);
}