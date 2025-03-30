ENTRY(main)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    . = 0x100000;  /* Adresse de chargement du noyau */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}