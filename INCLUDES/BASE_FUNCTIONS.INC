F_SET_VIDEO:;al=видеорежим
	mov ah,0
	int 10h
ret
;--------------------Печать Форматированной Строки-------------------------
F_PRINTSF:;ds:di-str,bl-color
    call F_GET_CURSOR
	xor cx,cx
	mov ah,013h
	push ds
	pop es
	mov cl,[ds:di]
	inc di
	mov bp,di
	mov bh,0
	mov al,1
	int 10h
ret
;-------------------Чтение видео режима------------------------------------------------------
F_READ_VIDEO:;out al=video ah=число колонок bh= номер активной страницы дисплея
    mov ah,0fh
    int 10h
ret
;------------Получение курсора; Выход: dh,dl - string,char ch,cl=нач.и кончеч строки курсора ----------------------------------------------------
F_GET_CURSOR:;out= dh,dl - string,char ch,cl=нач.и кончеч строки курсора
    call F_READ_VIDEO
    mov ah,03h
    int 10h
ret