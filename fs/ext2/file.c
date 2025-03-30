#include "ext2.h"
#include "../../kernel/kmalloc.h"

uint8_t* ext2_read_file(uint32_t inode_no, uint32_t* file_size) {
    struct ext2_inode inode = ext2_get_inode(inode_no);
    *file_size = inode.i_size;
    
    uint8_t* buffer = kmalloc(inode.i_size);
    uint32_t bytes_read = 0;
    
    // Parcours des blocs directs
    for (int i = 0; i < 12 && bytes_read < inode.i_size; i++) {
        if (inode.i_block[i] == 0) break;
        
        uint32_t to_read = MIN(EXT2_BLOCK_SIZE, inode.i_size - bytes_read);
        ext2_read_block(inode.i_block[i], buffer + bytes_read);
        bytes_read += to_read;
    }
    
    // TODO: Gérer les blocs indirects (niveau 1/2/3)
    return buffer;
}