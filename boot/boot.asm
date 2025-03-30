bits 16
org 0x7C00

start:
    ; Désactiver interruptions
    cli
    
    ; Configurer la pile
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Afficher un message
    mov si, msg
    call print
    hlt

print:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

msg db "Bootloader: Chargement du noyau...", 0

; Remplir le secteur (512 octets)
times 510 - ($-$$) db 0
dw 0xAA55  ; Signature BIOS