macro stringf str
{
    db .l-$-2,str,0
    .l:
}
macro string str
{
    db str,0
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
macro GET_STRING BUFFER, LEN
{
    mov ah,3
    push cs
    pop ds
    mov di,BUFFER
    mov cx,LEN
    int 90h
}
macro NEW_LINE
{
    mov ah,7
    int 90h
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
macro PRINT STR,COLOR
{
    mov ah,2
    push cs
    pop ds
    mov di,STR
    mov bl,COLOR
    int 90h
}
macro PRINT_CHAR CHAR
{
    mov al,CHAR
    mov ah,13h
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
macro CMP_STRING STR1, STR2
{
    push cs
    pop ds
    mov di, STR1
    mov si, STR2
    mov ah,09h
    int 90h
}
macro LOAD_DAPS DAPS
{
    push cs
    pop ds
    mov si, DAPS
    mov ah, 16h
    int 90h
}
macro LOAD_TABLE_FILES METKA
{
    push cs
    pop es
    mov bx,METKA
    mov ah,12h
    int 90h
}
macro SEACH_FILE TABLE_FILES, FILENAME
{
    push cs
    pop ds
    mov bx,TABLE_FILES
    mov di, FILENAME
    mov ah,10h
    int 90h
}
macro LOAD_FILE DOROGKA, SECTOR, NUM_SECTORS, SEGMENT, METKA
{
    mov dh,0
    mov ch,DOROGKA
    mov cl,SECTOR
    mov al,NUM_SECTORS
    push SEGMENT
    pop es
    mov bx, METKA
    mov ah,11h
    int 90h
}