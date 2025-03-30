// fs/ext2/ext2.h
#pragma once

#define EXT2_SUPER_MAGIC 0xEF53
#define EXT2_BLOCK_SIZE 1024

struct ext2_superblock {
    uint32_t s_inodes_count;
    uint32_t s_blocks_count;
    uint32_t s_first_data_block;
    // ... (autres champs)
    uint16_t s_magic;
};

struct ext2_inode {
    uint16_t i_mode;
    uint32_t i_size;
    uint32_t i_block[15];
};

struct ext2_dir_entry {
    uint32_t inode;
    uint16_t rec_len;
    uint8_t name_len;
    char name[];
};