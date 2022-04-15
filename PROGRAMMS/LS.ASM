org 0500h
main:

push cs
pop es
mov bx,tableFiles
mov ah,12h
int 90h
mov bx,tableFiles + 4
start:
    mov al,[bx]
    cmp al,0
    je exit
    push bx
    mov ah,02h
    push cs
    pop ds
    mov di,bx
    mov bl,00000111b
    int 90h
    mov ah,07h
    int 90h
    pop bx
    add bx,16
jmp start

exit:
int 91h
tableFiles:
times(512-($-main)) db 0