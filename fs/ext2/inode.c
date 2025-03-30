#include "ext2.h"

struct ext2_inode ext2_get_inode(uint32_t inode_no) {
    struct ext2_inode inode;
    uint32_t block_group = (inode_no - 1) / sb.s_inodes_per_group;
    uint32_t index = (inode_no - 1) % sb.s_inodes_per_group;
    
    // Calculer l'adresse du bloc
    uint32_t inode_table_block = sb.s_first_data_block + 1 + block_group * sb.s_blocks_per_group;
    uint32_t offset = index * sizeof(struct ext2_inode);
    
    disk_read(inode_table_block * 2, (uint8_t*)&inode, sizeof(inode)/512);
    return inode;
}