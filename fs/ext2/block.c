// fs/ext2/block.c
void ext2_read_block(uint32_t block_no, uint8_t* buffer) {
    uint32_t lba = block_no * (EXT2_BLOCK_SIZE / 512);
    disk_read(lba, buffer, EXT2_BLOCK_SIZE/512);
}