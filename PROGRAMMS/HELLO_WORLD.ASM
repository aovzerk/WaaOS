org 7E00h
main:
push cs
pop ds
mov di,str1
mov bl,00001111b
mov ah,02h
int 90h


int 91h

str1: db "Hello World!", 0
times(512-($-main)) db 0