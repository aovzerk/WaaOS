macro stringf str
{
    db .l-$-2,str,0
    .l:
}

macro SET_INTERRUPT_HANDLER NUM, HANDLER
{
    pusha
    xor ax,ax
    push ax
    pop es
    mov al,NUM
    mov bl,4h
    mul bl
    mov bx,ax
    mov si,HANDLER
    mov [es:bx],si
    add bx,2
    push cs
    pop ax
    mov [es:bx], ax
    popa
}
macro PRINTSF STR,COLOR
{
    mov ah,1
    push cs
    pop ds
    mov di,STR
    mov bl,COLOR
    int 90h
}
macro CALC_SIZE SIZE, START
{
    times(SIZE*512 - ($ - START)) db 0
}
macro NULL_REG
{
    xor ax,ax
    xor bx,bx
    xor cx,cx
    xor dx,dx
    xor si,si
    xor di,di
}