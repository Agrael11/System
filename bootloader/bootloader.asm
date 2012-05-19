[bits 16]
[org 0x7c00]

mov [drive], dl
mov cx, [drive]
push cx

reset:
	mov ah, 0
	int 0x13
	jc reset

;load setup code from disk to memory
mov ax, 0x7e0
mov es, ax
mov ah, 0x02
mov dh, 0
mov ch, 0
mov cl, 0x02
mov al, 0x10
mov bx, 0
int 0x13

jmp 0x7e00

drive: db 0

times (510-($-$$)) db 0
DW 0xAA55