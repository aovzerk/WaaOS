;--------------------Ролучить символ с клавиатуры-------------------------
F_GET_KEY:;out = AL-ASCII AH-scancode
    xor ax,ax
    int 16h
ret
;--------------------Получить строку в буфер------------------------- 
;in - ds:di=buffer cx-len buffer
;out - строка в буфере и на экране
F_GET_STRING:
    push ds
    push di
    push cx
    call F_CLEAR_BUFFER
    pop cx
    pop di
    pop ds
    add cx,-1
    push cx
    xor cx,cx
    pop bx
    START_F_GET_STRING:
        cmp bx,cx
        je F_GET_STRING_MAX_CHAR
         
        call F_GET_KEY
        cmp al,0dh
        je F_GET_STRING_ENTER
        cmp al,08h
        je F_GET_STRING_BACKSPACE
        
        push bx
        mov [ds:di], al
        push cx
        call F_PRINT_CHAR
        call F_CHAR_CURSOR_INC 
        pop cx
        pop bx
        inc di
        inc cx
     jmp START_F_GET_STRING
F_GET_STRING_BACKSPACE:
cmp cx,0
je START_F_GET_STRING
push cx
push bx
call F_CHAR_CURSOR_DEC
xor ax,ax
call F_PRINT_CHAR
pop bx
pop cx
dec cx
dec di
mov [ds:di],al
jmp START_F_GET_STRING
F_GET_STRING_MAX_CHAR:

xor ax,ax
mov [ds:di], al
F_GET_STRING_MAX_CHAR_LOOP:
call F_GET_KEY
cmp al,0dh
je F_GET_STRING_ENTER
cmp al,08h
je F_GET_STRING_BACKSPACE
jmp F_GET_STRING_MAX_CHAR_LOOP  
F_GET_STRING_ENTER:

ret