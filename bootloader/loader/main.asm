[bits 16]
[extern loader]

pop cx
mov [drive], cx

call _enable_a20
call _install_gdt

mov	eax, cr0
or eax, 1
mov	cr0, eax
jmp 08h:protected

[bits 32]
protected:
	mov		ax, 0x10
	mov		ds, ax
	mov		ss, ax
	mov		es, ax

	call loader

halt:
	jmp halt

print:
    pushad

    .loop:
        lodsb
        or      al, al
        jz      .done
        mov     ah, 0x0e
        int     0x10
        jmp     .loop

    .done:
        popad
        ret

drive		dw 0


%include "bootloader/loader/inc/a20.asm"
%include "bootloader/loader/inc/gdt.asm"