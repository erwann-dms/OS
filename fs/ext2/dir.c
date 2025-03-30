#include "ext2.h"

void ext2_list_dir(uint32_t inode_no) {
    struct ext2_inode inode = ext2_get_inode(inode_no);
    
    for (int i = 0; i < 12; i++) {  // 12 blocs directs
        if (inode.i_block[i] == 0) break;
        
        uint8_t block[1024];
        disk_read(inode.i_block[i] * 2, block, 2);
        
        struct ext2_dir_entry *entry = (struct ext2_dir_entry*)block;
        while ((uint8_t*)entry < block + 1024) {
            if (entry->inode != 0) {
                char name[256];
                memcpy(name, entry->name, entry->name_len);
                name[entry->name_len] = '\0';
                print("%s\n", name);
            }
            entry = (void*)entry + entry->rec_len;
        }
    }
}