
use16
org 7c00h
cli             ;запрещаем прерывания
        xor ax,ax       ;обнуляем регистр ах
        mov ds,ax       ;настраиваем сегмент данных на нулевой адрес
        mov es,ax       ;настраиваем сегмент es на нулевой адрес
        mov ss,ax       ;настраиваем сегмент стека на нулевой адрес
        mov sp,07E00h   ;сегмент sp указывает на текущую вершину стека
sti         ;разрешаем прерывания

push cs
pop ds
mov si,paket
mov ah,42h
int 13h
jmp 0000:0500h

jmp $
paket:
db 16;const paksize
db 0;null
db 4;кол-во секторов
db 0;null
dw 0500h;смещение
dw 0;сегмент
dq 2;начало

include 'INCLUDES\CONST.INC'
times(512-2-($-07C00h)) db 0
db 055h,0AAh
;16 байт 1 сегмент