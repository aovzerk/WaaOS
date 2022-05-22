MAIN_INTERRUPT_HANDLER:


cmp ah,0;al=видеорежим
je HF_SET_VIDEO

cmp ah,1;ds:di-str,bl-color
je HF_PRINTSF

cmp ah,2;ds:di-str,bl-color
je HF_PRINT

;in - ds:di=buffer cx-len buffer
;out - строка в буфере и на экране
cmp ah,3
je HF_GET_STRING

cmp ah,4;-|-in - dh=string, dl=char
je HF_SET_CURSOR

cmp ah,5
je HF_CHAR_CURSOR_INC

cmp ah,6
je HF_CHAR_CURSOR_DEC

cmp ah,7
je HF_NEW_LINE

;-|-in - ds:di=str, cx=len
; |-out - cx=len
cmp ah,08
je HF_GET_LEN_STR

;in = ds:di - str1 ds:si - str2
; |-out - al=|=0{1 srting == 2 string}
;            |=1{1 srting != 2 string}
cmp ah,09h
je HF_CMP_STRING


;-|-in - ds:bx=tableFiles, ds:di=flename
; |-out - cl=sector, ah=numSectors
; |-except - not found - ax=0, cx=0 al=2
cmp ah,10h
je HF_SEACH_FILE

;in: dh - golovka
;	 ch - dorogka
;	 cl - sector
;	 al - num sectors
;	 es:bx - куда грузить
cmp ah,11h
je HF_LOAD_FILE

;-|-in - es=segment, bx=metka
; |-out - (load file table on ram)
cmp ah,12h
je HF_LOAD_TABLE_FILES

cmp ah,13h;al-char
je HF_PRINT_CHAR

cmp ah,14h;out = AL-ASCII AH-scancode
je HF_GET_KEY

cmp ah,15h;out= dh,dl - string,char ch,cl=нач.и кончеч строки курсора
je HF_GET_CURSOR



;in: dh - golovka
;	 ch - dorogka
;	 cl - sector
;	 al - num sectors
;	 es:bx - куда грузить
cmp ah,16h
je HF_LOAD_FILE_AND_START
cmp ah,17h;-|-in - ds:si - daps
je HF_LOAD_DAPS

cmp ah,18h;-|-in - ds:si - daps
je HF_SAVE_DAPS


cmp ah,19h;-|-in - ds:si - daps
je HF_START_LOADED_FILE


cmp ah,20h;-|-in - ds:si - daps
je HCOPY_DATA

cmp ah,21h
je HPOWER_OFF

cmp ah,22h
je HGET_PIXEL_COLOR

HF_SET_VIDEO:
    call F_SET_VIDEO
iret

HF_PRINTSF:
    call F_PRINTSF
iret

HF_PRINT:
    call F_PRINT
iret
HF_GET_STRING:
    call F_GET_STRING
iret

HF_SET_CURSOR:
    call F_SET_CURSOR
iret

HF_CHAR_CURSOR_INC:
    call F_CHAR_CURSOR_INC
iret

HF_CHAR_CURSOR_DEC:
    call F_CHAR_CURSOR_DEC
iret

HF_NEW_LINE:
    call F_NEW_LINE
iret

HF_GET_LEN_STR:
    call F_GET_LEN_STR
iret

HF_CMP_STRING:
    call F_CMP_STRING
iret

HF_SEACH_FILE:
    call F_SEACH_FILE
iret

HF_LOAD_FILE:
    call F_LOAD_FILE
iret

HF_LOAD_TABLE_FILES:
    call F_LOAD_TABLE_FILES
iret

HF_PRINT_CHAR:
    call F_PRINT_CHAR
iret

HF_GET_CURSOR:
    call F_GET_CURSOR
iret

HF_GET_KEY:

    call F_GET_KEY
iret
HF_LOAD_DAPS:
    call F_LOAD_DAPS
iret
HF_SAVE_DAPS:
    call F_SAVE_DAPS
iret
HCOPY_DATA:;bx - от куда di - куда cx - len
    ;mov bx, TMP
    HCOPY_DATA_start:
        mov al, [bx]
        mov [di],al
        inc di
        inc bx
    loop HCOPY_DATA_start
iret
HPOWER_OFF:
    MOV     AX,5301h
    XOR     BX,BX
    INT     15h
    MOV     AX,5308h
    MOV     BX,0FFFFh
    MOV     CX,0001h
    INT     15h
    MOV     AX,5307h
    MOV     BX,0001h
    MOV     CX,0003h
    INT     15h
iret
HF_START_LOADED_FILE:
    pusha
    push cs
    pop ds
    mov di, TMP
    mov cx, 254
    call F_CLEAR_BUFFER
    popa
    pusha
    mov cx,254
    mov di,TMP
    HF_START_LOADED_FILE_TMP:
        mov al,[bx] 
        mov [di], al
        inc bx
        inc di
    loop HF_START_LOADED_FILE_TMP
    popa
    push TMP
    call F_LOAD_DAPS
    jmp 0000:07E00h
HGET_PIXEL_COLOR:;si-image_data ;out al-color
   xor   al,al                ; здесь будет результат  
   mov   ah,byte[esi]     ; берём цвет(B). читаем сколько синего
   shr   ah,7                 ; сдвигаем вправо на 7 разрядов
   and   ah,0001b             ; бит(0) маски отвечает за синий цвет
   or    al,ah                ; если имеется, то выставляем в маске синий
   inc   esi                   ; берём цвет(G) (в BMP цвета идут BGR)
   mov   ah,byte[esi]     ; тоже/самое, только со сдвигом на 1 левее
   shr   ah,6                 ; сдвигаем вправо на 6 разрядов
   and   ah,0010b             ; бит(1) маски - зелёный цвет
   or    al,ah                ; выставляем зеленый
   inc   esi                   ; берём цвет(R). читаем кол-во красного
   mov   ah,byte[esi]     ; всё/тоже,
   shr   ah,5                 ;   ..только со-сдвигом вправо на 5
   and   ah,0100b             ; бит(2) маски - красный
   or    al,ah                ; имеется? выставляем красный
   inc   esi
   or    al,1000b 
iret
HF_LOAD_FILE_AND_START:
    call F_LOAD_FILE
    pop ax
    pop bx
    pop cx
    xor ax,ax
    xor bx,bx
    xor cx,cx
    jmp 0000:07E00h