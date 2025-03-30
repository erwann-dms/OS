bits 16
org 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Affiche un message
    mov si, msg
    call print
    jmp load_kernel

print:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

load_kernel:
    ; Charge le noyau depuis le disque (LBA)
    mov ah, 0x02
    mov al, 10       ; Nombre de secteurs à lire
    mov ch, 0        ; Cylindre
    mov cl, 2        ; Secteur (après le bootloader)
    mov dh, 0        ; Tête
    mov bx, 0x1000   ; Adresse de chargement (ES:BX)
    int 0x13
    jmp 0x1000:0000  ; Saute au noyau

msg db "Bootloader: Chargement du noyau...", 0
times 510 - ($-$$) db 0
dw 0xAA55