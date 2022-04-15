macro PRINT STRING
{
    pusha
    mov ah,02h
    mov di,STRING
    push cs
    pop ds
    mov bl,00000111b
    int 90h
    popa
}
macro NEW_LINE
{
    pusha
    mov ah,07h
    int 90h
    popa
}
macro LOAD_TABLE_FILES METKA
{
    push cs
    pop es
    mov bx,METKA
    mov ah,12h
    int 90h
}
use16
org 0500h
main:

LOAD_TABLE_FILES tableFiles
mov bx,tableFiles + 4
start:
    mov al,[bx]
    cmp al,0
    je exit
    PRINT bx
    NEW_LINE
    add bx,16
jmp start

exit:
int 91h
tableFiles:
times(512-($-main)) db 0