ENTRY(kernel_main)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    . = 0x100000;  /* Adresse de chargement */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}