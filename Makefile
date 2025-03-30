KERNEL_OBJS = kernel/shell.o kernel/kmalloc.o
FS_OBJS = fs/ext2/super.o fs/ext2/inode.o fs/ext2/dir.o fs/ext2/file.o fs/ext2/block.o fs/disk/ata.o

all: myos.iso

myos.iso: $(KERNEL_OBJS) $(FS_OBJS)
    $(LD) -T kernel.ld -o kernel.elf $^
    grub-mkrescue -o $@ isodir/