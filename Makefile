CC = i686-elf-gcc
ASM = nasm
LD = i686-elf-ld

all: myos.iso

kernel.elf: kernel/main.o kernel/interrupts.o kernel/vga.o
    $(LD) -T kernel/linker.ld -o boot/kernel.elf $^

%.o: %.c
    $(CC) -c $< -o $@ -ffreestanding -nostdlib -O2

boot.bin: boot/boot.asm
    $(ASM) -f bin $< -o $@

myos.iso: kernel.elf
    mkdir -p isodir/boot/grub
    cp boot/kernel.elf isodir/boot/
    cp boot/grub/grub.cfg isodir/boot/grub/
    grub-mkrescue -o $@ isodir/

clean:
    rm -f *.o boot/*.bin boot/*.elf myos.iso