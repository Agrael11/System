[bits 16]

_install_gdt:
    pusha
    lgdt [gdt]
    popa
    ret

gdt_start:
    ; null - 0x0
    dd 0
    dd 0

    ; code - 0x8
    dw 0xffff
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0

    ; data - 0x10
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

    ; 16 bit code - 0x18
    dw 0xffff
    dw 0
    db 0
    db 10011010b
    db 10001111b
    db 0

    ; 16 bit data - 0x20
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 10001111b
    db 0

gdt_end:

gdt:
    dw gdt_end - gdt_start - 1
    dd gdt_start