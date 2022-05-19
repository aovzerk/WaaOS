F_CLEAR_SCREEN:
	mov al,03h
	call F_SET_VIDEO
ret
F_SET_VIDEO:;al=видеорежим
	mov ah,0
	int 10h
ret
;--------------------Печать Форматированной Строки-------------------------
F_PRINTSF:;ds:di-str,bl-color
    call F_GET_CURSOR
	xor cx,cx
	mov cl,[ds:di]
	inc di
	MAIN_START_F_PRINTSF:
		call F_READ_VIDEO
		mov ah,013h
		push ds
		pop es
		mov bp,di
		mov al,1
		int 10h
ret
;--------------------Печать Строки-------------------------
F_PRINT:;ds:di-str,bl-color
	push di
	push ds
	call F_GET_CURSOR
	call F_GET_LEN_STR
	pop ds
	pop di
	call MAIN_START_F_PRINTSF
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
;-------------------Фуекция подсчета длины строки.------------------------------------------------------------------------------

;-|-in - ds:di=str, cx=len
; |-out - cx=len
F_GET_LEN_STR:
	xor cx,cx
	START_F_GET_LEN_STR:
	mov al,[ds:di]
	cmp al,0
	je EXIT_F_GET_LET_STR
	inc di
	inc cx
	jmp START_F_GET_LEN_STR
	EXIT_F_GET_LET_STR:
ret
;--------------------Печать одного символа-------------------------
F_PRINT_CHAR:;al-char
	push ax
	call F_READ_VIDEO
	pop ax
	mov ah,0ah
	mov cx,1
	int 10h
ret
;-------------Установить позицию курсора-------------------------------------------------------------------------------------------------

;-|-in - dh=string, dl=char
; |-out - (cursor set on position)
F_SET_CURSOR:
	push dx
	call F_READ_VIDEO
	pop dx
	mov ah,02h
	int 10h
ret
;--------------увеличить позицию курсора на 1---------------------------------------------------------------------------------

;---out - (cursor increment position)
F_CHAR_CURSOR_INC:
	call F_GET_CURSOR
	inc dl
	call F_SET_CURSOR
ret

;-----------уменьшить позицию курсора на 1 1--------------------------------------------------------------------------------------

;---out - (cursor decrement position)
F_CHAR_CURSOR_DEC:
	call F_GET_CURSOR
	dec dl
	call F_SET_CURSOR
ret
;-------------------Ставит курсор на новую строку-------------------------------------------------------------------------------

;---out - (cursor on next string)
F_NEW_LINE:
	call F_GET_CURSOR
	mov dl,0
	inc dh
	call F_SET_CURSOR
	cmp dh,24
	je F_CLEAR_SCREEN
ret


;-------------------Очистка памяти----------------------------------------------------------------------------------------------

;-|-in - ds:di=buffer, cx=size
; |-out - (clear buffer)
F_CLEAR_BUFFER:
	xor ax,ax
	F_CLEAR_BUFFER_START:
	mov [ds:di],al
	inc di
	loop F_CLEAR_BUFFER_START
ret
;--------------Сравнение строк--------------------------------------------------------------------------------------------------
;in = ds:di - str1 ds:si - str2
; |-out - al=|=0{1 srting == 2 string}
;            |=1{1 srting != 2 string}
F_CMP_STRING:
	push di
	push si

	call F_GET_LEN_STR
	push cx
	mov di,si
	call F_GET_LEN_STR
	pop ax
	cmp ax,cx
	je F_CMP_STRING_START1 
	pop si
	pop di
	jmp F_CMP_STRING_EXIT


	F_CMP_STRING_START1:
	pop si
	pop di
	F_CMP_STRING_START:
	mov al,[ds:di]
	mov ah,[ds:si] 

	cmp cx,0
	je F_CMP_STRING_EXIT2
	dec cx

	inc di
	inc si

	cmp al,ah
	je F_CMP_STRING_START

F_CMP_STRING_EXIT:
	mov al,1;!=
	jmp F_CMP_STRING_GLOBAL_EXIT

F_CMP_STRING_EXIT2:
	mov al,0;==
	jmp F_CMP_STRING_GLOBAL_EXIT

F_CMP_STRING_GLOBAL_EXIT:
ret

;-------------------Поиск адреса файла------------------------------------------------------------------------------------------

;-|-in - ds:bx=tableFiles, ds:di=flename
; |-out - ch-dorogka cl=sector, al=numSectors ah = type
; |-except - not found - ax=0, cx=0
F_SEACH_FILE:
jmp startpfseachFile
	pfseachFilecxsave: db 0
	pfseachFilebxsave: db 0,0
	pfseachFiledisave: db 0,0
	startpfseachFile:
	xor cx,cx
	mov cl,32
	add bx,4
	mov [pfseachFiledisave],di
	startSeach:
	mov [pfseachFilecxsave],cl
	mov [pfseachFilebxsave],bx
	mov di,[pfseachFiledisave]
	mov si,[pfseachFilebxsave]
	call F_CMP_STRING
	cmp al,0
	je pgetDataForstartFile
	mov cl,[pfseachFilecxsave]
	mov bx,[pfseachFilebxsave]
	add bx,16
	loop startSeach
	xor bx,bx
	xor cx,cx
	xor ax,ax
	jmp exitpfseachFile
	pgetDataForstartFile:
	mov bx,[pfseachFilebxsave]
	mov di,bx
	dec di
	mov cl,[ds:di]
	dec di
	mov ch,[ds:di]
	mov al,ch
	dec di
	mov ch,[ds:di]
	dec di
	mov ah,[ds:di]
	exitpfseachFile:
ret

;-------------------Загрузка файла------------------------------------------------------------------------------------------
;in: dh - Номер головки(read/write)(0 - read)
;	 ch - dorogka
;	 cl - sector
;	 al - num sectors
;	 es:bx - куда грузить
F_LOAD_FILE:
	mov ah,02h
	mov dl,[BOOT_DISK]
	int 13h
ret

;-------------------Загрузка таблицы файлов-------------------------------------------------------------------------------------

;-|-in - es=segment, bx=metka
; |-out - (load file table on ram)
F_LOAD_TABLE_FILES:
	mov ah,02h
	mov dh,0
	mov dl,[BOOT_DISK]
	mov ch,0
	mov cl,2
	mov al,1
	int 13h
ret

;-------------------Загрузка DAPS-------------------------------------------------------------------------------------

;-|-in - ds:si - daps
; |-out - (load file table on ram)
F_LOAD_DAPS:
	mov dl,[BOOT_DISK]
	mov ah,42h
	int 13h
ret
F_SAVE_DAPS:
	mov dl,[BOOT_DISK]
	mov ah,43h
	int 13h
ret