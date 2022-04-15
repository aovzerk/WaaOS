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