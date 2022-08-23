org 0500h
GLOBAL:
mov [BOOT_DISK],dl
jmp START_K
;-----------------------------------------------------------
    include 'INCLUDES\MACROS.INC'
    include 'INCLUDES\BASE_FUNCTIONS.INC'
    include 'INCLUDES\INTERRUPT_HANDLER_RETURN.INC'
    include 'INCLUDES\MAIN_INTERRUPT_HANDLER.INC'
    include 'INCLUDES\KEYBOARD.INC'
    include 'INCLUDES\CONST.INC'
;-----------------------------------------------------------
START_K:
SET_INTERRUPT_HANDLER 90H,MAIN_INTERRUPT_HANDLER
SET_INTERRUPT_HANDLER 91H,INTERRUPT_HANDLER_RETURN
LOAD_DAPS DAPS_TABEL_FILES
PRINT HELLO_WORLD, BLACK
MAIN:
;NEW_LINE
;PRINT INPUT_STR, BLACK
;GET_STRING BUFFER, 13
SEACH_FILE TABLE_FILES, CMD
cmp ax,0
je PRINT_ERROR


cmp ah,1
je START_PROGRAMM
jmp MAIN

START_PROGRAMM:
    mov si, DAPS_RUNTIME_FILE
    mov di,SIZE_RUN_PROGRAMM
    mov [di], al
    add al,al
    add cl,cl
    mov [si + 2], al
    mov [si + 8], cl
    LOAD_DAPS DAPS_RUNTIME_FILE
    ;LOAD_FILE ch, cl, al, 0000, 0500h
    NEW_LINE
jmp 0000:7E00h

PRINT_ERROR:
    NEW_LINE
    PRINT ERROR, RED
jmp MAIN


RETURN_INT:
    jmp MAIN
;сюда передает управление int 91h
jmp $
DAPS_RUNTIME_FILE:
    db 16;const paksize
    db 0;null
    db 1;кол-во секторов
    db 0;null
    dw 7E00h;смещение
    dw 0;сегмент
    dq 7;начало
DAPS_TABEL_FILES:
    db 16;const paksize
    db 0;null
    db 1;кол-во секторов
    db 0;null
    dw TABLE_FILES;смещение
    dw 0;сегмент
    dq 1;начало
HELLO_WORLD: string "R-OS Loaded, Hello! =)"
ERROR: string "Command not found :("
CMD: string "cmd"
INPUT_STR: string "user:>"
BOOT_DISK: db 0
SIZE_RUN_PROGRAMM: db 6
BUFFER: db 13 dup(0)
TMP: db 255 dup(0)
TABLE_FILES:
CALC_SIZE SIZE_KERNEL, GLOBAL