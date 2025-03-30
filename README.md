Ouvrez le fichier pour le lire correctement

Mon OS:

structure:

myos/
├── boot/
│   ├── boot.asm    # Bootloader (ASM)
│   └── grub/
│       └── grub.cfg  # Configuration GRUB
├── kernel/
│   ├── main.c      # Noyau en C
│   └── linker.ld   # Script de linkage
└── Makefile        # Automatisation


Les outils:

Outil                              Rôle                                              Installation (Linux)
GCC (Cross-Compiler)	             Compiler le noyau sans dépendances système	       sudo apt install gcc gcc-multilib
NASM	                             Compiler le bootloader en assembleur	             sudo apt install nasm
GRUB + XORRISO	                   Générer une ISO bootable	                         sudo apt install grub2-common grub-pc-bin xorriso
QEMU	                             Tester l’ISO sans VM	                             sudo apt install qemu-system-x86
GDB	                               Déboguer le noyau	                               sudo apt install gdb

Pour compiler le bootloader:
nasm -f bin boot/boot.asm -o boot/boot.bin

Pour compiler le noyau:
i686-elf-gcc -c kernel/main.c -o kernel/main.o -ffreestanding -nostdlib -O2 -Wall -Wextra

Pour lier le noyau:
i686-elf-ld -T kernel/linker.ld -o boot/kernel.elf kernel/main.o --oformat=elf32-i386

Générer l'ISO bootable:
dd if=boot/boot.bin of=myos.iso bs=512 count=1 conv=notrunc
