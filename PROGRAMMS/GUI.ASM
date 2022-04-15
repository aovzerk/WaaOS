macro LOAD_TABLE_FILES METKA
{
    push cs
    pop es
    mov bx,METKA
    mov ah,12h
    int 90h
}
macro SET_CURSOR x,y
{
    mov dh,y
    mov dl,x
    mov ah,04h
    int 90h
}
macro PRINT_SELECTED STRING
{
    ;PRINT_PREFIX
    mov ah,02h
    push cs
    pop ds
    mov di,STRING
    mov bl,01110001b
    int 90h
}
macro PRINT STRING
{
    mov ah,02h
    push cs
    pop ds
    mov di,STRING
    mov bl,00011111b
    int 90h
}
macro PRINTC STRING, COLOR
{
    mov ah,02h
    push cs
    pop ds
    mov di,STRING
    mov bl,COLOR
    int 90h
}
macro PRINT_PREFIX
{
    GET_CURSOR
    add dl,-3
    SET_CURSOR dl,dh
    mov ah,02h
    push cs
    pop ds
    mov di,PREFIX
    mov bl,00011111b
    int 90h
}

macro GET_CURSOR
{
    mov ah,15h
    int 90h
}
macro GET_KEY
{
    mov ah,14h
    int 90h
}
macro string str
{
    db str,0
}
macro PRINT_WALLC LEN
{
    mov cx,LEN
    call PRINT_WALL2
}
macro PRINT_BORDER
{
    SET_CURSOR 1,1
    PRINTC wall,01110001b
    PRINT_WALLC 23
    SET_CURSOR 24,1
    PRINT_WALLC 23
    SET_CURSOR 1,1
    PRINT_WALLC 23
    SET_CURSOR 1,23
    PRINTC wall,01110001b
}
use16
org 0500h
main:
LOAD_TABLE_FILES TABLE_FILES
call FILL_SCREAN
PRINT_BORDER
mov bx,TABLE_FILES + 4
DRAW_FILENAMES:
    push bx
    mov ah,[x]
    mov al,[y]
    SET_CURSOR ah,al
    pop bx
    mov al,[bx]
    cmp al,0
    je init_input
    push bx
    PRINT bx
    pop bx
    add bx,16
    mov al,[y]
    inc al
    mov [y],al
    jmp DRAW_FILENAMES
init_input:
SET_CURSOR 3,3
mov bx,TABLE_FILES + 4
mov [selected], bx
mov al,3
mov [y],al
PRINT_SELECTED bx
SET_CURSOR 0,25
input:
    GET_KEY
    cmp ah,50h
    je down
    cmp ah,48h
    je up
    cmp al,0dh
    je start_up
jmp input
down:
    mov bx,[selected]
    add bx,16
    mov al,[bx]
    cmp al,0
    je input
    sub bx,16
    mov ah,[x]
    mov al,[y]
    push bx
    SET_CURSOR ah,al
    pop bx
    push bx
    PRINT bx
    pop bx
    add bx,16
    mov [selected], bx
    mov ah,[x]
    mov al,[y]
    inc al
    mov [y],al
    push bx
    SET_CURSOR ah,al
    pop bx
    PRINT_SELECTED bx
    SET_CURSOR 0,25
jmp input
up:
    mov bx,[selected]
    mov ah,[x]
    mov al,[y]
    push bx
    SET_CURSOR ah,al
    pop bx
    push bx
    PRINT bx
    pop bx
    sub bx,16
    mov [selected], bx
    mov ah,[x]
    mov al,[y]
    dec al
    cmp al,2
    je correct
    mov [y],al
    push bx
    SET_CURSOR ah,al
    pop bx
    PRINT_SELECTED bx
    SET_CURSOR 0,25
jmp input
start_up:
    mov ax,0003h
    int 10h
    mov di,[selected]
    dec di
	mov cl,[ds:di]
	dec di
	mov ch,[ds:di]
	mov al,ch
	dec di
	mov ch,[ds:di]
	dec di
	mov ah,[ds:di]
    mov dh,0
    mov ch,0
    mov ah,16h
    push 0000
    pop es
    mov bx,0500h
    int 90h
jmp input
correct:
    inc al
    SET_CURSOR ah,al
    mov bx,[selected]
    add bx,16
    mov [selected], bx
    PRINT_SELECTED bx
    SET_CURSOR 0,25
jmp input
jmp $
int 91h
x: db 3
y: db 3
PREFIX: string "-->"
wall2: string " "
wall: string "                                                                          "
selected: db 0,0
PRINT_WALL2:;cx-len
    START_PRINT_WALL2:
        push cx
        PRINTC wall2,01110001b
        
        GET_CURSOR
        inc dh
        dec dl
        SET_CURSOR dl,dh
        pop cx
    loop START_PRINT_WALL2
ret
FILL_SCREAN:
    mov ax,0003h
    int 10h
    mov ah,00010000b
    mov al,0
    push 0B800h
    pop es
    xor di,di
    mov cx,3840
    fill:
        stosw
    loop fill
ret


TABLE_FILES:
times(2*512-($-main)) db 0
